/* Minimal program */
#include "stm32f4xx.h" 
#include <stdint.h> 

int main (void)
{
    extern uint32_t SystemCoreClock;
    /* Update systemCoreClock variable */
    SystemCoreClockUpdate();
    /* Enable PORT G clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    /* Set mode to output */
    GPIOG->MODER |= (1 << (13*2));
    /* Set pin high if SystemCoreClock is what we think it is */
    if ((SystemCoreClock == 180000000) && ((RCC->CFGR & RCC_CFGR_PPRE1) == RCC_CFGR_PPRE1_DIV4)) {
        GPIOG->ODR |= (1 << 13);
    }
    /* To setup UART with baudrate of 115200 we do the following calculation
     * DIV = (CPU_FREQ / APBx_PRESCALAR)/(16*115200)
     * (in this case 0x187 is a good div value */
    /* Enable PORT C clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    /* Enable UART5 clock */
    RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    /* Set to alternate function */
    GPIOC->MODER |= (1 << (12*2)) + 1;
    GPIOC->AFR[1] &= ~(0xf << 16);
    GPIOC->AFR[1] |= (0x8 << 16);
    /* Set speed fast */
    GPIOC->OSPEEDR |= (0x3 << (2*12));
    /* Set open drain */
    GPIOC->OTYPER |= GPIO_OTYPER_ODR_12;
    /* Set Baud Rate */
    UART5->BRR = 0x187;
    /* Enable UART */
//    UART5->CR1 |= USART_CR1_UE | USART_CR1_TE;
    while (1) {
        /* Wait for previous bytes to transmit */
        while (!(UART5->SR & USART_SR_TC));
        /* Transmit something */
        UART5->DR = 'a'; 
        int n;
        for (n = 0; n < 8000000; n++) {
        }
//        GPIOG->ODR ^= (1 << 13);
    }
    while (1);
}
