//
//  main.c
//  AX12A_Drive_C
//
//  Created by ����ƫ�� on 2020/8/3.
//  Copyright ? 2020 ����ƫ��. All rights reserved.
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	
	
	
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
		if(times%30==0) LED0=!LED0;//��˸LED,��ʾϵͳ��������.
		delay_ms(10);   
		times++;
	}
}

