#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_KEY_RCU RCU_GPIOA
#define BSP_KEY_PORT GPIOA
#define BSP_KEY_PIN GPIO_PIN_0

#define BSP_KEY_IRQN EXTI0_IRQn
#define BSP_KEY_EXTI_PORT EXTI_SOURCE_GPIOA
#define BSP_KEY_EXTI_PIN EXTI_SOURCE_PIN0
#define BSP_KEY_EXTI_LINE EXTI_0

#define BSP_KEY_EXTI_IRQHandler EXTI0_IRQHandler



void key_gpio_config(void);
void key_scan(void);

extern uint8_t count;
#endif
