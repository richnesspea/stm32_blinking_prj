#ifndef __INC_STM32F4XX_H__
#define __INC_STM32F4XX_H__

#include <stdint.h>

#define __vo volatile

//Base address of flash and ram memory
//RM: We use Main flash memory boot mode -> see the table 3
#define FLASH_BASEADDR  0x08000000U        
#define SRAM1_BASEADDR  0x20000000U       
#define SRAM2_BASEADDR  0x2001C000U       
#define ROM             0x1FFF0000U
#define SRAM            SRAM1_BASEADDR

//AHB and APB Bus Peripheral base addresses
//RM: Table 1 
#define APB1PERIPH_BASE 0x40000000U
#define APB2PERIPH_BASE 0x40010000U
#define AHB1PERIPH_BASE 0x40020000U
#define AHB2PERIPH_BASE 0x50000000U
#define AHB3PERIPH_BASE 0xA0000000U
#define PERIPH_BASE     APB1PERIPH_BASE

//Base addresses of peripherals which are hanging on AHB1 
#define GPIOA_BASEADDR (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR (AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASEADDR (AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASEADDR (AHB1PERIPH_BASE + 0x2800)
//#define CRC_BASEADDR   (AHB1PERIPH_BASE + 0x3000)
#define RCC_BASEADDR   (AHB1PERIPH_BASE + 0x3800)

//Peripheral register definition structures
//RM: GPIO register map (Table 40)
typedef struct {
    __vo uint32_t MODER;         //offset: 0x00
    __vo uint32_t OTYPER;        //offset: 0x04
    __vo uint32_t OSPEEDR;       //offset: 0x08
    __vo uint32_t PUPDR;         //offset: 0x0C
    __vo uint32_t IDR;           //offset: 0x10
    __vo uint32_t ODR;           //offset: 0x14
    __vo uint32_t BSRR;          //offset: 0x18
    __vo uint32_t LCKR;          //offset: 0x1C
    __vo uint32_t AFR[2];        //offset: 0x20
}GPIO_RegDef_t; //GPIO register definition

//RM: RCC register map (table 35)
typedef struct {
    __vo uint32_t CR;
    __vo uint32_t PLLCFGR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;
    __vo uint32_t AHB1RSTR;
    __vo uint32_t AHB2RSTR;
    __vo uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    __vo uint32_t APB1RSTR;
    __vo uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    __vo uint32_t AHB1ENR;
    __vo uint32_t AHB2ENR;
    __vo uint32_t AHB3ENR;
    uint32_t RESERVED2;
    __vo uint32_t APB1ENR;
    __vo uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    __vo uint32_t AHB1LPENR;
    __vo uint32_t AHB2LPENR;
    __vo uint32_t AHB3LPENR;
    uint32_t RESERVED4;
    __vo uint32_t APB1LPENR;
    __vo uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    __vo uint32_t BDCR;
    __vo uint32_t CSR;
    uint32_t RESERVED6[2];
    __vo uint32_t SSCGR;
    __vo uint32_t PLLI2SCFGR;
}RCC_RegDef_t;


// GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t*)0x40020000;// Declare one pointer that points to one address in memory (0x40020000)
// GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t*)GPIOA_BASEADDR;
// pGPIOA->MODER = 25;

#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ ((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK ((GPIO_RegDef_t*)GPIOK_BASEADDR)
#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)


//Clock Enable Macros for GPIOx peripherals
//RM: 7.3.10 : RCC AHB1 peripheral clock enable register
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1 << 0)) 
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1 << 1)) 
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1 << 3))


//Clock Disable Macro for GPIOx peripherals
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0)) 
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 1)) 
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 2)) 
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 3)) 

//Some generic macros
#define ENABLE          1
#define DISABLE         0
#define SET             ENABLE
#define RESET           DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET

#include "GPIO.h"


#endif