#include "bsp_adc.h"

void adc_config(void)
{
	
	//使能引脚时钟
	rcu_periph_clock_enable(BSP_ADC0_PORT_RCU);
	//使能ADC时钟
	rcu_periph_clock_enable(BSP_ADC0_RCU);
	//配置ADC时钟-30MHZ
	adc_clock_config(ADC_ADCCK_PCLK2_DIV4);
	
	//配置引脚为模拟输入模式
	gpio_mode_set(BSP_ADC0_PORT,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,BSP_ADC0_PIN);

	/*adc配置*/
	//配置独立模式
	adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT);

	//使能扫描模式
	adc_special_function_config(BSP_ADC0,ADC_SCAN_MODE,ENABLE);
	
	//数据右对齐
	adc_data_alignment_config(BSP_ADC0,ADC_DATAALIGN_RIGHT);
	
	//ADC设置为12位分辨率
	adc_resolution_config(BSP_ADC0,ADC_RESOLUTION_12B);
	
	//ADC0设置为规则组，使用一个通道
	adc_channel_length_config(BSP_ADC0,ADC_REGULAR_CHANNEL,1);
	
	//adc外部触发禁用，只使用软件触发
	adc_external_trigger_config(BSP_ADC0,ADC_REGULAR_CHANNEL,EXTERNAL_TRIGGER_DISABLE);
	
	//ADC使能
	adc_enable(BSP_ADC0);
	
	//开启ADC自校准
	adc_calibration_enable(BSP_ADC0);
}

unsigned int Get_ADC_Value(uint8_t ADC_CHANNEL_x)
{
		unsigned int adc_value=0;
		
		//设置采集通道
		adc_regular_channel_config(BSP_ADC0,0,ADC_CHANNEL_x,ADC_SAMPLETIME_15);
	//软件转换
		adc_software_trigger_enable(BSP_ADC0,ADC_REGULAR_CHANNEL);
		//等待ADC采样完成
		while (adc_flag_get(BSP_ADC0,ADC_FLAG_EOC)==RESET)
		{
			;
		}
		//读取采样值
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

