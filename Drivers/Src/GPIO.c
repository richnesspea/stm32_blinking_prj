#include "GPIO.h"

/* GPIO API requirements
1. GPIO initialization
2. Enable/Disable GPIO port clock
3. Read from a GPIO Pin
4. Write to a GPIO Pin
5. Configure alternate functionality
6. Interrupt handling
*/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOB){
            GPIOB_PCLK_EN();
        }
        else if (pGPIOx == GPIOC){
            GPIOC_PCLK_EN();
        }
        else if (pGPIOx == GPIOD){
            GPIOD_PCLK_EN();
        }
        else if (pGPIOx == GPIOE){
            GPIOE_PCLK_EN();
        }
    }
    else {
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_DI();
        }
        else if (pGPIOx == GPIOB){
            GPIOB_PCLK_DI();
        }
        else if (pGPIOx == GPIOC){
            GPIOC_PCLK_DI();
        }
        else if (pGPIOx == GPIOD){
            GPIOD_PCLK_DI();
        }
        else if (pGPIOx == GPIOE){
            GPIOE_PCLK_DI();
        }
    }
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

    uint32_t temp = 0;

    // 1. Configure the mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
        // non-interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//PD12 and output -> 1 << (2x12) = 1 << 24
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing bits
        pGPIOHandle->pGPIOx->MODER |= temp; //Setting bits 
        temp = 0;
    }

    else {
    // 2. Configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//PD12 and output -> 1 << (2x12) = 1 << 24
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;
    temp = 0;
    // 3. Configure the pull-up/pull-down
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); 
    pGPIOHandle->pGPIOx->PUPDR |= temp;
    temp = 0; 
    // 4. Configure the output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 
    pGPIOHandle->pGPIOx->OTYPER |= temp;
    temp = 0;
    
    // 5. Configure the alt functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALT){ //PD12
            uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; //temp1 = 1 => AFRH
            uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; //temp2 = 4 
            pGPIOHandle->pGPIOx->AFR[temp1] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2); // AFRH |= value << (4 x 4)
        }
    }
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint16_t Value){
    if(Value == GPIO_PIN_SET){
        pGPIOx->ODR |= (1 << PinNumber); 
    }
    else {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}


