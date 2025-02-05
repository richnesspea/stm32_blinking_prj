    .section .isr_vector, "a", %progbits
    .global _vector_table
    
_vector_table:
    .word   _estack                 // Stack pointer (định nghĩa trong linker script)
    .word   Reset_Handler           // Reset Handler
    .word   NMI_Handler             // NMI Handler
    .word   HardFault_Handler       // Hard Fault Handler
    .word   MemManage_Handler       // MPU Fault Handler
    .word   BusFault_Handler        // Bus Fault Handler
    .word   UsageFault_Handler      // Usage Fault Handler
    .word   0                       // Reserved
    .word   0                       // Reserved
    .word   0                       // Reserved
    .word   0                       // Reserved
    .word   SVC_Handler             // SVCall Handler
    .word   DebugMon_Handler        // Debug Monitor Handler
    .word   0                       // Reserved
    .word   PendSV_Handler          // PendSV Handler
    .word   SysTick_Handler         // SysTick Handler

    // Các ISR khác tùy thuộc vào ngoại vi sử dụng
    .word   GPIOA_IRQHandler        // GPIOA Interrupt
    .word   GPIOB_IRQHandler        // GPIOB Interrupt
    .word   GPIOC_IRQHandler        // GPIOC Interrupt
    .word   GPIOD_IRQHandler        // GPIOD Interrupt
    .word   RCC_IRQHandler          // RCC Interrupt
    
    .section .text
    .thumb

Reset_Handler:
    ldr     r0, =_estack          // Load the stack pointer into r0
    mov     sp, r0                // Set sp from r0
    bl      SystemInit            // Call the system initialization function
    bl      main                  // Call the main function
    b       .                     // Infinite loop if main returns

    .weak SystemInit
    .thumb_set SystemInit,Default_Handler
    .weak main
    .thumb_set main,Default_Handler

Default_Handler:
    b       .                       // Lặp vô hạn nếu có lỗi

    .weak NMI_Handler
    .thumb_set NMI_Handler, Default_Handler
    .weak HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler
    .weak MemManage_Handler
    .thumb_set MemManage_Handler, Default_Handler
    .weak BusFault_Handler
    .thumb_set BusFault_Handler, Default_Handler
    .weak UsageFault_Handler
    .thumb_set UsageFault_Handler, Default_Handler
    .weak SVC_Handler
    .thumb_set SVC_Handler, Default_Handler
    .weak DebugMon_Handler
    .thumb_set DebugMon_Handler, Default_Handler
    .weak PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler
    .weak SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler
    .weak GPIOA_IRQHandler
    .thumb_set GPIOA_IRQHandler, Default_Handler
    .weak GPIOB_IRQHandler
    .thumb_set GPIOB_IRQHandler, Default_Handler
    .weak GPIOC_IRQHandler
    .thumb_set GPIOC_IRQHandler, Default_Handler
    .weak GPIOD_IRQHandler
    .thumb_set GPIOD_IRQHandler, Default_Handler
    .weak RCC_IRQHandler
    .thumb_set RCC_IRQHandler, Default_Handler
    