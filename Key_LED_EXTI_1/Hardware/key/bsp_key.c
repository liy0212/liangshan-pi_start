#include "bsp_key.h"
#include "bsp_led.h"
#include <stdio.h>



void key_gpio_config(void)
{
	rcu_periph_clock_enable(BSP_KEY_RCU);
	
	rcu_periph_clock_enable(RCU_SYSCFG);//系统配置时钟
	
	gpio_mode_set(BSP_KEY_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,BSP_KEY_PIN);
	
	gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN);
	
	//连接中断线 
	syscfg_exti_line_config(BSP_KEY_EXTI_PORT,BSP_KEY_EXTI_PIN);
	
	exti_init(BSP_KEY_EXTI_LINE,EXTI_INTERRUPT,EXTI_TRIG_RISING);//初始化外部中断
	
	//使能中断
	exti_interrupt_enable(BSP_KEY_EXTI_LINE);
	
	//清除中断标志位
	exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
}

void key_scan(void)
{
	if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
	{
		delay_1ms(20);
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
		{
			//执行功能
			
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET);//等待按键松开
			gpio_bit_toggle(PORT_LED1,PIN_LED1);
		}		
	}
}

void BSP_KEY_EXTI_IRQHandler(void)
{
	if((exti_interrupt_flag_get(BSP_KEY_EXTI_LINE))==SET)  
	{
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
	{
		delay_1ms(20);
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
		{
			//执行功能
			
		
	
			//while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET);//等待按键松开
			
			
			
	}
		exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
	}
	
	}
}
