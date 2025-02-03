#include "GPIO.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOD){
            GPIOD_PCLK_EN();
        }
    }
    else {
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_DI();
        }
        else if (pGPIOx == GPIOD){
            GPIOD_PCLK_DI();
        }
    }
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

    
}


