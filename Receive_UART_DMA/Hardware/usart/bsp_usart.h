#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>

#define BSP_USART_TX_RCU RCU_GPIOA
#define BSP_USART_RX_RCU RCU_GPIOA
#define BSP_USART_RCU RCU_USART0

#define BSP_USART_TX_PORT GPIOA
#define BSP_USART_RX_PORT GPIOA
#define BSP_USART_AF GPIO_AF_7
#define BSP_USART_TX_PIN GPIO_PIN_9
#define BSP_USART_RX_PIN GPIO_PIN_10

#define BSP_USART USART0
#define BSP_USART_IRQN USART0_IRQn

#define USART_RECEIVE_LENGTH 4096
#define BSP_USART_IRQHandler USART0_IRQHandler

void usart_gpio_config(uint32_t band_rate);
void usart_send_data(uint8_t ucch);
void usart_send_string(uint8_t *ucstr);
int fputc(int ch,FILE *f);


extern uint8_t g_recv_buff[USART_RECEIVE_LENGTH];
extern uint16_t g_recv_length ;
extern uint8_t g_recv_complete_flag;
#endif

