#include "bsp_key.h"
#include "bsp_led.h"
#include <stdio.h>

uint8_t count=0;

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
			gpio_bit_toggle(PORT_LED1,PIN_LED1);
			printf("按下\r\n");
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET);//等待按键松开
			printf("松开\r\n");
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
			
			printf("按下,");
			count++;
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET);//等待按键松开
			printf("松开%d\r\n",count);
			
		if(count<1)
		{
			count=1;
		}
			switch(count)
		{
			case 1:{gpio_bit_toggle(PORT_LED1,PIN_LED1);printf("点亮LED1\r\n");break;}
			case 2:{gpio_bit_toggle(PORT_LED2,PIN_LED2);printf("点亮LED2\r\n");break;}
			case 3:{gpio_bit_toggle(PORT_LED3,PIN_LED3);printf("点亮LED3\r\n");break;}
			case 4:{gpio_bit_toggle(PORT_LED4,PIN_LED4);printf("点亮LED4\r\n");break;}
    }
		if(count>=4)
		{
			count=0;
		}
			
	}
		exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
	}
	
	}
}
