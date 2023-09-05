#include <stdio.h>
#include "bsp_usart.h"

uint8_t g_recv_buff[USART_RECEIVE_LENGTH];
uint16_t g_recv_length =0;
uint8_t g_recv_complete_flag=0;

void usart_gpio_config(uint32_t band_rate)
{
	rcu_periph_clock_enable(BSP_USART_RX_RCU);//PA9,PA10
	rcu_periph_clock_enable(BSP_USART_RCU);
	
	//���ô��ڸ���
	gpio_af_set(BSP_USART_RX_PORT, BSP_USART_AF,BSP_USART_TX_PIN);
	gpio_af_set(BSP_USART_TX_PORT, BSP_USART_AF,BSP_USART_RX_PIN);
	
	//���ø���ģʽ
	gpio_mode_set(BSP_USART_TX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_TX_PIN);
	gpio_mode_set(BSP_USART_RX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_RX_PIN);
	
	//���������50MHZ
	gpio_output_options_set(BSP_USART_TX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_TX_PIN);
	gpio_output_options_set(BSP_USART_RX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_RX_PIN);
	
	//��λ����
	usart_deinit(BSP_USART);
	//���ò�����
	usart_baudrate_set(BSP_USART,band_rate);
	//����У��λ
	usart_parity_config(BSP_USART,USART_PM_NONE);
	//��������λ
	usart_word_length_set(BSP_USART,USART_WL_8BIT);
	//����ֹͣλ
	usart_stop_bit_set(BSP_USART,USART_STB_1BIT);
	 
	//ʹ��
	usart_enable(BSP_USART);
	usart_transmit_config(BSP_USART, USART_TRANSMIT_ENABLE);
	usart_receive_config(BSP_USART, USART_RECEIVE_ENABLE);//ʹ�ܽ���
	
	nvic_irq_enable(BSP_USART_IRQN,2,2);//�����ж����ȼ�
	
	usart_interrupt_enable(BSP_USART,USART_INT_RBNE);//�����ж�
	
	usart_interrupt_enable(BSP_USART,USART_INT_IDLE);//�����ж�
}

void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(BSP_USART,(uint8_t)ucch);
	while(RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE)); //Ϊ������ѭ�������ͻ�����δ������ִ��
}
	
void usart_send_string(uint8_t *ucstr)
{
	while(ucstr && *ucstr)//��ַΪ�ջ���ֵΪ��ʱ����
	{
		usart_send_data(*ucstr++);
	}
}

int fputc(int ch,FILE *f)
{
	usart_send_data(ch);
	return ch;
}

void BSP_USART_IRQHandler(void)
{
	if(usart_interrupt_flag_get(BSP_USART,USART_INT_FLAG_RBNE)==SET)//�����ж�
	{
		g_recv_buff[g_recv_length++]=usart_data_receive(BSP_USART);
	}
	if(usart_interrupt_flag_get(BSP_USART,USART_INT_FLAG_IDLE)==SET)//�����ж�
	{
		usart_data_receive(BSP_USART);
		g_recv_buff[g_recv_length]='\0';//��ӽ�����
		g_recv_complete_flag=1;//��ɱ�־λ
	}
}