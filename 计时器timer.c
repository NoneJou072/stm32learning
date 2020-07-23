#include<timer.h>
#include<led.h>

int temp=0;
int t2=0;

void TIM3_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	TIM_TimeBaseInitStrue.TIM_Period=arr;
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);
	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	TIM_Cmd(TIM3,ENABLE);
	
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		temp++;
		if(temp==10)temp=0,t2++;
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
