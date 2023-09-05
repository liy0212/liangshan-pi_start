#ifndef __BSP_IIC_H_

#define __BSP_IIC_H_

#include "gd32f4xx.h"
#include "systick.h"

//端口
#define RCU_SDA RCU_GPIOB
#define PORT_SDA GPIOB
#define PIN_SDA GPIO_PIN_9

#define RCU_SCL RCU_GPIOB
#define PORT_SCL GPIOB
#define PIN_SCL GPIO_PIN_8

//SDA输出模式
#define SDA_OUT() gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,PIN_SDA)

//SDA输入模式
#define SDA_IN() gpio_mode_set(PORT_SDA,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,PIN_SDA)

//获取SDA引脚电平
#define SDA_GET() gpio_input_bit_get(PORT_SDA,PIN_SDA)

//SDA与SCL输出
#define SDA(x) gpio_bit_write(PORT_SDA,PIN_SDA,(x?SET:RESET))
#define SCL(x) gpio_bit_write(PORT_SCL,PIN_SCL,(x?SET:RESET))
#endif
