#include "bsp_pwm.h"

	/*GPIO���ò���,���ڲ�����*/
static void pwm_gpio_config(void)
{

	//ʹ��ʱ��
	rcu_periph_clock_enable(BSP_PWM_RCU);
	//����ģʽ���������������
	gpio_mode_set(BSP_PWM_PORT, GPIO_MODE_AF,GPIO_PUPD_NONE,BSP_PWM_PIN);
	//�������
	 gpio_output_options_set(BSP_PWM_PORT, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, BSP_PWM_PIN);
	//���ø��ù���
	gpio_af_set(BSP_PWM_PORT,BSP_PWM_AF,BSP_PWM_PIN);
}


	/*��ʱ������*/
void pwm_config(uint16_t pre,uint16_t per)
{	
	timer_parameter_struct timere_initpara;
	timer_oc_parameter_struct timer_ocintpara;
	pwm_gpio_config();


	//������ʱ��ʱ��	
	rcu_periph_clock_enable(BSP_PWM_TIMER_RCU);

	//���ö�ʱ��ʱ��Ϊ4��Ƶ��200MHZ
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	//��ʼ����ʱ��
	timer_deinit(BSP_PWM_TIMER);
	
		timere_initpara.prescaler         = pre-1;
    timere_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timere_initpara.counterdirection  = TIMER_COUNTER_UP;//���ϼ���
    timere_initpara.period            = per-1;
		timere_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timere_initpara.repetitioncounter = 0U;
	
	timer_init(BSP_PWM_TIMER,&timere_initpara);
	
	//����ṹ��
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;//ʹ��PWM������˿�
	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;//���ͨ���ߵ�ƽ��Ч
	timer_channel_output_config(BSP_PWM_TIMER,TIMER_CH_0,&timer_ocintpara);
	
	//ռ�ձ�����
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,0);
	
	timer_channel_output_mode_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,TIMER_OC_MODE_PWM0);
	//����������������
	timer_channel_output_shadow_config(BSP_PWM_TIMER,BSP_PWM_TIMER_CH,TIMER_OC_SHADOW_DISABLE);
	//�Զ�װ��
	timer_auto_reload_shadow_enable(BSP_PWM_TIMER);
	/*��ʱ�����ȼ����ã����߼���ʱ��������*/
	//timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);
	
	timer_enable(BSP_PWM_TIMER);

}

void pwm_breathing_lamp(void)
{
	static uint8_t direct=0;//����
	static uint16_t value=0;//�ߵ�ƽռ�ձ�
	
	if(direct==0)//����
	{
		value+=300;
		if(value>=10000)
		{
			direct=1;
		}
	}
	else//�䰵
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

