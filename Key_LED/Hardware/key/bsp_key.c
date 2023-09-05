#include "bsp_key.h"
#include "bsp_led.h"

void key_gpio_config(void)
{
	rcu_periph_clock_enable(BSP_KEY_RCU);
	
	gpio_mode_set(BSP_KEY_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,BSP_KEY_PIN);
	
	gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN);
}

void key_scan(void)
{
	if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
	{
		delay_1ms(20);
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET)
		{
			//ִ�й���
			gpio_bit_toggle(PORT_LED1,PIN_LED1);
			printf("����\r\n");
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) ==SET);//�ȴ������ɿ�
			printf("�ɿ�\r\n");
		}		
	}
}