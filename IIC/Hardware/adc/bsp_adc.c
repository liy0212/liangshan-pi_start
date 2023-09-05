#include "bsp_adc.h"

void adc_config(void)
{
	
	//ʹ������ʱ��
	rcu_periph_clock_enable(BSP_ADC0_PORT_RCU);
	//ʹ��ADCʱ��
	rcu_periph_clock_enable(BSP_ADC0_RCU);
	//����ADCʱ��-30MHZ
	adc_clock_config(ADC_ADCCK_PCLK2_DIV4);
	
	//��������Ϊģ������ģʽ
	gpio_mode_set(BSP_ADC0_PORT,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,BSP_ADC0_PIN);

	/*adc����*/
	//���ö���ģʽ
	adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT);

	//ʹ��ɨ��ģʽ
	adc_special_function_config(BSP_ADC0,ADC_SCAN_MODE,ENABLE);
	
	//�����Ҷ���
	adc_data_alignment_config(BSP_ADC0,ADC_DATAALIGN_RIGHT);
	
	//ADC����Ϊ12λ�ֱ���
	adc_resolution_config(BSP_ADC0,ADC_RESOLUTION_12B);
	
	//ADC0����Ϊ�����飬ʹ��һ��ͨ��
	adc_channel_length_config(BSP_ADC0,ADC_REGULAR_CHANNEL,1);
	
	//adc�ⲿ�������ã�ֻʹ���������
	adc_external_trigger_config(BSP_ADC0,ADC_REGULAR_CHANNEL,EXTERNAL_TRIGGER_DISABLE);
	
	//ADCʹ��
	adc_enable(BSP_ADC0);
	
	//����ADC��У׼
	adc_calibration_enable(BSP_ADC0);
}

unsigned int Get_ADC_Value(uint8_t ADC_CHANNEL_x)
{
		unsigned int adc_value=0;
		
		//���òɼ�ͨ��
		adc_regular_channel_config(BSP_ADC0,0,ADC_CHANNEL_x,ADC_SAMPLETIME_15);
	//���ת��
		adc_software_trigger_enable(BSP_ADC0,ADC_REGULAR_CHANNEL);
		//�ȴ�ADC�������
		while (adc_flag_get(BSP_ADC0,ADC_FLAG_EOC)==RESET)
		{
			;
		}
		//��ȡ����ֵ
		adc_value = adc_regular_data_read(BSP_ADC0);
		
		return adc_value;
}

unsigned int adc_filter(unsigned int num)
{
		int i=0;
	unsigned int value=0;
	for(i=0;i<num;i++)
	{
		value+=Get_ADC_Value(BSP_ADC_CHANNEL);
		delay_1ms(1);
	}
	value=value/num;
	return value;
}

