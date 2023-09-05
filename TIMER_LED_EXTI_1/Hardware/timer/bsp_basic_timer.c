#include "bsp_basic_timer.h"
#include "bsp_led.h"  
#include <stdio.h>
//������ʱ��5
void basic_timer_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	//������ʱ��ʱ��	
	rcu_periph_clock_enable(BSP_BASIC_TIMER_RCU);

	//���ö�ʱ��ʱ��Ϊ4��Ƶ��200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//��ʼ����ʱ��
	timer_deinit(BSP_BASIC_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//���ϼ���
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_BASIC_TIMER,&timere_initpara);
	
	nvic_irq_enable(BSP_BASIC_TIMER_IRQ,3,2);
	//ʹ�ܶ�ʱ���ж�
	timer_interrupt_enable(BSP_BASIC_TIMER,TIMER_INT_UP);
	//������ʱ��
	timer_enable(BSP_BASIC_TIMER);
}

void BSP_BASIC_TIMER_IRQHANDER(void)
{
	if(timer_interrupt_flag_get(BSP_BASIC_TIMER,TIMER_INT_FLAG_UP)==SET)
	{
		timer_interrupt_flag_clear(BSP_BASIC_TIMER,TIMER_INT_FLAG_UP);
		/* ��ӹ��� */
		gpio_bit_toggle(PORT_LED1,PIN_LED1);
		printf("��ʱ��5�����ж�\r\n");
	
	}
}

//��ʱ��2
void timer_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	//������ʱ��ʱ��	
	rcu_periph_clock_enable(BSP_TIMER_RCU);

	//���ö�ʱ��ʱ��Ϊ4��Ƶ��200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//��ʼ����ʱ��
	timer_deinit(BSP_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//���ϼ���
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_TIMER,&timere_initpara);
	
	nvic_irq_enable(BSP_TIMER_IRQ,2,3);
	//ʹ�ܶ�ʱ���ж�
	timer_interrupt_enable(BSP_TIMER,TIMER_INT_UP);
	//������ʱ��
	timer_enable(BSP_TIMER);
}

void BSP_TIMER_IRQHANDER(void)
{
	if(timer_interrupt_flag_get(BSP_TIMER,TIMER_INT_FLAG_UP)==SET)
	{
		timer_interrupt_flag_clear(BSP_TIMER,TIMER_INT_FLAG_UP);
		/* ��ӹ��� */
		gpio_bit_toggle(PORT_LED2,PIN_LED2);
		printf("��ʱ��2�����ж�\r\n");
	
	}
}

