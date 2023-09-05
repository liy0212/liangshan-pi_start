#ifndef __BSP_DMA_H
#define __BSP_DMA_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_DMA_RCU RCU_DMA1//DMA ±÷”
#define BSP_DMA DMA1//dma
#define BSP_DMA_CH DMA_CH2//DMAÕ®µ¿

#define BSP_DMA_CH_IRQ DMA1_Channel2_IRQn
#define BSP_DMA_CH_IRQ_HANDLER DMA1_Channel2_IRQHandler
void dam_config(void);
#endif
