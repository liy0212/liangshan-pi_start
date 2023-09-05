#include "bsp_iic.h"

void iic_gpio_config(void)
{
	//ʹ��ʱ��
	rcu_periph_clock_enable(RCU_SDA);
	rcu_periph_clock_enable(RCU_SCL);
	
	//����SDA,��©�����50Mhz
	gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,PIN_SDA);
	gpio_output_options_set(PORT_SDA,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,PIN_SDA);
	
		
	//����SCL,��©�����50Mhz
	gpio_mode_set(PORT_SCL,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,PIN_SCL);
	gpio_output_options_set(PORT_SCL,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,PIN_SCL);
}

//��ʼ�ź�
void iic_start(void)
{
	SDA_OUT();
	SCL(1);
	SDA(1);
	delay_1us(5);
	SDA(0);
	delay_1us(5);
	SCL(0);
	delay_1us(5);
}

//ֹͣ�ź�
void iic_stop(void)
{
	SDA_OUT();
	SCL(0);
	SDA(0);
	SCL(1);
	delay_1us(5);
	SDA(1);
	delay_1us(5);
}

//���ͷ�Ӧ��
void iic_send_nack(void)
{
	SDA_OUT();
	SCL(0);
	SDA(0);
	SCL(1);
	SDA(1);
	delay_1us(5);
	SCL(0);
	SDA(0);
}

//����Ӧ��
void iic_send_ack(void)
{
	SDA_OUT();
	SCL(0);
	SDA(1);
	SCL(1);
	SDA(0);
	delay_1us(5);
	SCL(0);
	SDA(1);
}

//�ȴ��ӻ�Ӧ��
unsigned char iic_WaitAck(void)
{
	char ack=0;
	unsigned char ack_flag=10;
	SCL(0);
	SDA(1);
	SDA_IN();
	delay_1us(5);
	SCL(1);
	delay_1us(5);
	
	while((SDA_GET()==1)&&(ack_flag))
	{
		ack_flag--;
		delay_1us(5);
	}
	
	//��Ӧ��
	if(ack_flag<=0)
	{
		iic_stop();
		return 1;
	}
	//Ӧ��
	else
	{
		SCL(0);
		SDA_OUT();
	}
	return ack;
}

//����1�ֽ�
void iic_send_byte(uint8_t dat)
{
	int i=0;
	SDA_OUT();
	SCL(0);
	
	for(i=0;i<8;i++)
	{
		SDA((dat&&0x80)>>7);
		delay_1us(1);
		SCL(1);
		delay_1us(5);
		SCL(0);
		delay_1us(5);
		dat<<=1;
	}
}


//����1�ֽ�
unsigned char iic_read_byte(void)
{
	unsigned char i,receive=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
		SCL(0);
		delay_1us(5);
		SCL(1);
		delay_1us(5);
		receive<<=1;
		if(SDA_GET())
		{
			receive|=1;
		}
	}
	SCL(1);
	return receive;
}

