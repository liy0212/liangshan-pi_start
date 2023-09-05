#include "bsp_led.h"  





void led_gpio_config(void)
{	
	//使能时钟
	rcu_periph_clock_enable(RCU_GPIOD);
	//配置模式，配置输出，浮空
	gpio_mode_set(PORT_LED1, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_LED1);
	//配置输出
	 gpio_output_options_set(PORT_LED1, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, PIN_LED1);
}