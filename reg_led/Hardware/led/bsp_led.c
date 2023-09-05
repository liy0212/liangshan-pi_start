#include "bsp_led.h"  





void led_gpio_config(void)
{
	//开启GPIOD时钟
	BSP_RCU_AHB1EN |=(1<<3);
	 
	
 //配置GPIO模式
	//配置输出
	BSP_GPIOD_CTL &=  ~(0x03<<(2*7));
	BSP_GPIOD_CTL |= (0x01<<(2*7));
	
	//配置浮空
	BSP_GPIOD_PUD &=~(0X03<<(2*7));
	BSP_GPIOD_PUD |= (0x00<<(2*7));
	//设置GPIO输出
	//配置输出模式
	BSP_GPIOD_OMODE&=~(0X01<<7);
	//配置输出速度寄存器
	BSP_GPIOD_OSPD &=~(0X03<<(2*7));
	BSP_GPIOD_OSPD |= (0x02<<(2*7));
}