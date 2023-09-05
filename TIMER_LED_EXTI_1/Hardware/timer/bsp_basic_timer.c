#include "bsp_basic_timer.h"
#include "bsp_led.h"  
#include <stdio.h>
//基本定时器5
void basic_timer_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	//开启定时器时钟	
	rcu_periph_clock_enable(BSP_BASIC_TIMER_RCU);

	//配置定时器时钟为4倍频，200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//初始化定时器
	timer_deinit(BSP_BASIC_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//向上计数
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_BASIC_TIMER,&timere_initpara);
	
	nvic_irq_enable(BSP_BASIC_TIMER_IRQ,3,2);
	//使能定时器中断
	timer_interrupt_enable(BSP_BASIC_TIMER,TIMER_INT_UP);
	//开启定时器
	timer_enable(BSP_BASIC_TIMER);
}

void BSP_BASIC_TIMER_IRQHANDER(void)
{
	if(timer_interrupt_flag_get(BSP_BASIC_TIMER,TIMER_INT_FLAG_UP)==SET)
	{
		timer_interrupt_flag_clear(BSP_BASIC_TIMER,TIMER_INT_FLAG_UP);
		/* 添加功能 */
		gpio_bit_toggle(PORT_LED1,PIN_LED1);
		printf("定时器5触发中断\r\n");
	
	}
}

//定时器2
void timer_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	//开启定时器时钟	
	rcu_periph_clock_enable(BSP_TIMER_RCU);

	//配置定时器时钟为4倍频，200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//初始化定时器
	timer_deinit(BSP_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//向上计数
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_TIMER,&timere_initpara);
	
	nvic_irq_enable(BSP_TIMER_IRQ,2,3);
	//使能定时器中断
	timer_interrupt_enable(BSP_TIMER,TIMER_INT_UP);
	//开启定时器
	timer_enable(BSP_TIMER);
}

void BSP_TIMER_IRQHANDER(void)
{
	if(timer_interrupt_flag_get(BSP_TIMER,TIMER_INT_FLAG_UP)==SET)
	{
		timer_interrupt_flag_clear(BSP_TIMER,TIMER_INT_FLAG_UP);
		/* 添加功能 */
		gpio_bit_toggle(PORT_LED2,PIN_LED2);
		printf("定时器2触发中断\r\n");
	
	}
}

