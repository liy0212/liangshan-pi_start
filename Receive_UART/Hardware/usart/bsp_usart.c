#include <stdio.h>
#include "bsp_usart.h"

uint8_t g_recv_buff[USART_RECEIVE_LENGTH];
uint16_t g_recv_length =0;
uint8_t g_recv_complete_flag=0;

void usart_gpio_config(uint32_t band_rate)
{
	rcu_periph_clock_enable(BSP_USART_RX_RCU);//PA9,PA10
	rcu_periph_clock_enable(BSP_USART_RCU);
	
	//配置串口复用
	gpio_af_set(BSP_USART_RX_PORT, BSP_USART_AF,BSP_USART_TX_PIN);
	gpio_af_set(BSP_USART_TX_PORT, BSP_USART_AF,BSP_USART_RX_PIN);
	
	//配置复用模式
	gpio_mode_set(BSP_USART_TX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_TX_PIN);
	gpio_mode_set(BSP_USART_RX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_RX_PIN);
	
	//推挽输出，50MHZ
	gpio_output_options_set(BSP_USART_TX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_TX_PIN);
	gpio_output_options_set(BSP_USART_RX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_RX_PIN);
	
	//复位串口
	usart_deinit(BSP_USART);
	//配置波特率
	usart_baudrate_set(BSP_USART,band_rate);
	//配置校验位
	usart_parity_config(BSP_USART,USART_PM_NONE);
	//配置数据位
	usart_word_length_set(BSP_USART,USART_WL_8BIT);
	//配置停止位
	usart_stop_bit_set(BSP_USART,USART_STB_1BIT);
	 
	//使能
	usart_enable(BSP_USART);
	usart_transmit_config(BSP_USART, USART_TRANSMIT_ENABLE);
	usart_receive_config(BSP_USART, USART_RECEIVE_ENABLE);//使能接收
	
	nvic_irq_enable(BSP_USART_IRQN,2,2);//配置中断优先级
	
	usart_interrupt_enable(BSP_USART,USART_INT_RBNE);//接收中断
	
	usart_interrupt_enable(BSP_USART,USART_INT_IDLE);//空闲中断
}

void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(BSP_USART,(uint8_t)ucch);
	while(RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE)); //为空跳出循环，发送缓冲区未满继续执行
}
	
void usart_send_string(uint8_t *ucstr)
{
	while(ucstr && *ucstr)//地址为空或者值为空时跳出
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
	if(usart_interrupt_flag_get(BSP_USART,USART_INT_FLAG_RBNE)==SET)//接收中断
	{
		g_recv_buff[g_recv_length++]=usart_data_receive(BSP_USART);
	}
	if(usart_interrupt_flag_get(BSP_USART,USART_INT_FLAG_IDLE)==SET)//空闲中断
	{
		usart_data_receive(BSP_USART);
		g_recv_buff[g_recv_length]='\0';//添加结束符
		g_recv_complete_flag=1;//完成标志位
	}
}