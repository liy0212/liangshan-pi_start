#include "bsp_pwm.h"

	/*GPIO配置部分,仅内部调用*/
static void pwm_gpio_config(void)
{

	//使能时钟
	rcu_periph_clock_enable(BSP_PWM_RCU);
	//配置模式，配置输出，浮空
	gpio_mode_set(BSP_PWM_PORT, GPIO_MODE_AF,GPIO_PUPD_NONE,BSP_PWM_PIN);
	//配置输出
	 gpio_output_options_set(BSP_PWM_PORT, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, BSP_PWM_PIN);
	//配置复用功能
	gpio_af_set(BSP_PWM_PORT,BSP_PWM_AF,BSP_PWM_PIN);
}


	/*定时器部分*/
void pwm_config(uint16_t pre,uint16_t per)
{	
	timer_parameter_struct timere_initpara;
	timer_oc_parameter_struct timer_ocintpara;
	pwm_gpio_config();


	//开启定时器时钟	
	rcu_periph_clock_enable(BSP_PWM_TIMER_RCU);

	//配置定时器时钟为4倍频，200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//初始化定时器
	timer_deinit(BSP_PWM_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//向上计数
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_PWM_TIMER,&timere_initpara);
	
	//输出结构体
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;//使能PWM输出到端口
	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;//输出通道高电平有效
	timer_channel_output_config(BSP_PWM_TIMER,TIMER_CH_0,&timer_ocintpara);
	
	//占空比配置
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,0);
	
	timer_channel_output_mode_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,TIMER_OC_MODE_PWM0);
	//不启用死区发生器
	timer_channel_output_shadow_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,TIMER_OC_SHADOW_DISABLE);
	//自动装载
	timer_auto_reload_shadow_enable(BSP_PWM_TIMER);
	/*定时器优先级配置，仅高级定时器需配置*/
	//timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);
	
	timer_enable(BSP_PWM_TIMER);

}

void pwm_breathing_lamp(void)
{
	static uint8_t direct=0;//方向
	static uint16_t value=0;//高电平占空比
	
	if(direct==0)//变亮
	{
		value+=300;
		if(value>=10000)
		{
			direct=1;
		}
	}
	else//变暗
	{
		value-=300;
		if(value<=0)
		{
			direct=0;
		}
	}
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,value);
	delay_1ms(50);
}

