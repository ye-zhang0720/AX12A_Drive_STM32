//
//  main.c
//  AX12A_Drive_C
//
//  Created by 西北偏北 on 2020/8/3.
//  Copyright ? 2020 西北偏北. All rights reserved.
//

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "Dynamixel.h"


int main(void)
{ 
	unsigned short temp = 0;
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
	
	
	
	while(1)
	{
		
		if(times%300 == 0)
		{
			ping(1);
		}
		if(times%30==0)
		{

			temp = readDxlResult();
	
			
			if(temp != 0xffff)
			{
				unsigned char tmp[2];
				tmp[0] = (unsigned char)temp%0xff;
				tmp[1] = (unsigned char)temp/0xff;
				USART1_Send_Data(tmp,2);
			}
		}
		if(times%30==0) LED0=!LED0;//闪烁LED,提示系统正在运行.
		delay_ms(10);   
		times++;
	}
}

