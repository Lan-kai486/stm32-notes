#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA 的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //定时器的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP ;//复用推挽，交给定时器
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2); //用内部72MHz的时钟
	//配置时基单元
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period= 100 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler= 720 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter= 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//配输出比较
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//先给所有成员一个默认值 
	//原因：C 语言的局部变量不会自动清零，它拿到的是栈上残留的旧数据。这个结构体有七八个成员，你只填 4 个，剩下那几个就是垃圾值。
    //关键在于：TIM_OC1Init() 会把结构体里所有成员都写进寄存器，包括你没填的那些。垃圾值会真的写进硬件，于是出现莫名其妙的死机、输出异常、偶尔好偶尔坏。
    //TIM_OCStructInit() 做的就是把库里预设的安全默认值一次性铺满所有成员，相当于先整张表填一遍默认值，你再改需要的几格。
    //不是“配置不上会随机”，而是“没填的字段本身就是随机值，而且会一起被交上去”。
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1 ;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High ;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_Cmd(TIM2,ENABLE);
}

																																									