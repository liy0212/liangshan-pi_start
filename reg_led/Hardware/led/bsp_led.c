#include "bsp_led.h"  





void led_gpio_config(void)
{
	//����GPIODʱ��
	BSP_RCU_AHB1EN |=(1<<3);
	 
	
 //����GPIOģʽ
	//�������
	BSP_GPIOD_CTL &=  ~(0x03<<(2*7));
	BSP_GPIOD_CTL |= (0x01<<(2*7));
	
	//���ø���
	BSP_GPIOD_PUD &=~(0X03<<(2*7));
	BSP_GPIOD_PUD |= (0x00<<(2*7));
	//����GPIO���
	//�������ģʽ
	BSP_GPIOD_OMODE&=~(0X01<<7);
	//��������ٶȼĴ���
	BSP_GPIOD_OSPD &=~(0X03<<(2*7));
	BSP_GPIOD_OSPD |= (0x02<<(2*7));
}