#include "stm32f4xx.h"

void delay(void){
    for(uint32_t i = 0; i < 50000; i++);
}


//Blinking LED1 = PD12
int main(void){
    GPIO_Handle_t GpioLed;
    GpioLed.pGPIOx = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PU_PD; //When using push-pull, dont need pull-up or down anymore

    GPIO_PeriClockControl(GPIOD, ENABLE);
    GPIO_Init(&GpioLed);
    while(1){
        GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_SET);
        delay();
        GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_RESET);
        delay();
    }
    return 0;
}