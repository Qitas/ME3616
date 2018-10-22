#include "sys.h"
#include "usart.h"	  
#include "delay.h"

u8 Uart1_Receive_Mark = 0;
u8 Uart1_Receive_Value_Num = 0;
char Uart1_Receive_Array[100];	

u8 Uart2_Receive_Mark = 0;
u8 Uart2_Receive_Value_Num = 0;
char Uart2_Receive_Array[100];	

/*----------------------------
	����2��ʼ��
-----------------------------*/
void Uart2_Init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//GPIOAʱ��, PA2��PA3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2, PA2��PA3
	USART_DeInit(USART2);  //��λ����2
	
	//USART2_TX  --> PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 							//PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); 									//��ʼ��PA2

	//USART2_RX	 --> PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  								//��ʼ��PA3

	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;							//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); 							//��ʼ������2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);					//��������2�ж�
	USART_Cmd(USART2, ENABLE);                    					//ʹ�ܴ���2 
}

/*----------------------------
	����1��ʼ��
-----------------------------*/
void Uart1_Init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//GPIOAʱ��, PA9��PA10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1, PA9��PA10
	USART_DeInit(USART1);  //��λ����1
	
	//USART1_TX  --> PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 							//PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); 									//��ʼ��PA2

	//USART1_RX	 --> PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  								//��ʼ��PA10

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;							//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); 							//��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);					//��������1�ж�
	USART_Cmd(USART1, ENABLE);                    					//ʹ�ܴ���1 
}

/*----------------------------
	����2�жϷ������
----------------------------*/
void USART2_IRQHandler(void)                							
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  	//�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Uart2_Receive_Mark = 1;
		Uart2_Receive_Array[Uart2_Receive_Value_Num++] = USART_ReceiveData(USART2);		
	} 
} 

/*----------------------------
	����1�жϷ������
----------------------------*/
void USART1_IRQHandler(void)                							
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  	//�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Uart1_Receive_Mark = 1;
		Uart1_Receive_Array[Uart1_Receive_Value_Num++] = USART_ReceiveData(USART1);		
	} 
} 

/*----------------------------
	����2�����ַ���
----------------------------*/
void Uart2_SendString(char *s)
{
    while (*s)   
    {
        Uart2_SendData(*s++);       
    }
}

/*----------------------------
	����1�����ַ���
----------------------------*/
void Uart1_SendString(char *s)
{
    while (*s)   
    {
        Uart1_SendData(*s++);       
    }
}

/*----------------------------
	����2��������
----------------------------*/
void Uart2_SendData(u8 dat)
{
	while((USART2->SR&0X40)==0);//�ȴ����ͽ���
	USART_SendData(USART2, dat);
}

/*----------------------------
	����1��������
----------------------------*/
void Uart1_SendData(u8 dat)
{
	while((USART1->SR&0X40)==0);//�ȴ����ͽ���
	USART_SendData(USART1, dat);
}

/*----------------------------
	����2������
----------------------------*/
void Uart2_Method(void)
{
	if(Uart2_Receive_Mark == 1)
	{
		delay_ms(300);
		Uart2_Receive_Array[Uart2_Receive_Value_Num] = '\0';	
		Uart1_SendString(Uart2_Receive_Array);
		Uart2_Receive_Value_Num = 0;
		Uart2_Receive_Mark = 0;
	}
}

/*----------------------------
	����1������
----------------------------*/
void Uart1_Method(void)
{
	if(Uart1_Receive_Mark == 1)
	{
		delay_ms(300);
		Uart1_Receive_Array[Uart1_Receive_Value_Num] = '\0';	
		Uart2_SendString(Uart1_Receive_Array);
		Uart1_Receive_Value_Num = 0;
		Uart1_Receive_Mark = 0;
	}
}
