#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_ADC0_PORT_RCU RCU_GPIOC
#define BSP_ADC0_RCU RCU_ADC0

#define BSP_ADC0 ADC0

#define BSP_ADC0_PORT GPIOC
#define BSP_ADC0_PIN GPIO_PIN_1

#define BSP_ADC_CHANNEL ADC_CHANNEL_11
void adc_config(void);
unsigned int Get_ADC_Value(uint8_t ADC_CHANNEL_x);
unsigned int adc_filter(unsigned int num);
#endif
