/******************************************************************************
						STM32F103RCT6 

���ܣ�ME3616-C1A COAPͨ������

Ӳ��ԭ��ͼ:  	TXD1    -->   PA.9
							RXD1    -->   PA.10

							TXD2    -->   PA.2
							RXD2    -->   PA.3

Ӳ�����ӣ�����1ͨ��USBת����оƬ�ӵ�PC������2ͨ����ƽת����·�ӵ���Ƭ����
����˵����PC����ͨ���������ַ������ݸ�����1������1͸��������2������2���͸�NB-IOTģ�飬
		  NB-IOT���ݷ��͵�����2��͸��������1���Ӷ�ʵ��NBģ��ͨѶ��ͬʱPC���ܽ������

�����ʣ�115200
******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "usart.h"

int main(void)
{	
	u8 i;
	
	delay_init();	    	 		// ��ʱ������ʼ��	
	NVIC_Configuration();		// �����ж����ȼ�����
	
	Uart1_Init(115200);	 		// ���ڳ�ʼ��Ϊ115200
	Uart2_Init(115200);	 		// ���ڳ�ʼ��Ϊ115200
	 
	Uart1_SendString("Doiot System Start.\r\n"); 	// PC��ʾϵͳ����
	for(i=0; i<60; i++)
	{
		delay_ms(1000);		// ȷ��ϵͳ�ȶ�
	}

	Uart2_SendString("AT\r\n");		
	delay_ms(100);	
	Uart2_SendString("ATI\r\n");		
	delay_ms(100);	
	Uart2_SendString("AT+CGSN=1\r\n");		
	delay_ms(100);		
	Uart2_SendString("AT+CSQ\r\n");		
	delay_ms(100);	
	Uart2_SendString("AT+CIMI\r\n");		
	delay_ms(100);	
	Uart2_SendString("AT+CEREG?\r\n");		
	delay_ms(100);	
	Uart2_SendString("AT+M2MCLINEW=180.101.147.115,5683,\"868613030006275\",90\r\n");		
	delay_ms(100);	
	for(i=0; i<20; i++)
	{
		delay_ms(1000);		// ȷ��ϵͳע����IOTƽ̨
	}
	Uart2_SendString("AT+M2MCLISEND=000101\r\n");		
	delay_ms(100);
	
	while(1)
	{
		Uart1_Method();				// ����1������
		Uart2_Method();				// ����2������
	}
}


