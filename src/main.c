/* Minimal program */
#include "stm32f4xx.h" 
#include <stdint.h> 
#include <stdio.h> 
#include <math.h> 

#define BAUD_RATE 9600UL 
int puts(const char *str)
{
    while (*str != '\0') {
        /* Wait for previous transfer to complete */
        while (!(UART5->SR & USART_SR_TXE));
        /* Transmit something */
        UART5->DR = *str; 
        str++;
    }
}

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
    GPIOG->ODR |= (1 << 13);
    /* Enable PORT C clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    /* Enable UART5 clock */
    RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    /* Set to alternate function */
    GPIOC->MODER &= ~(0x3 << (12*2));
    GPIOC->MODER |= (1 << ((12*2)+1));
    GPIOC->AFR[1] &= ~(0xf << 16);
    GPIOC->AFR[1] |= (0x8 << 16);
    /* Enable UART */
    UART5->CR1 |= USART_CR1_UE;
    UART5->CR1 &= ~USART_CR1_M;
    /* Set Baud Rate */
    /* To setup UART with baudrate of 9600 we do the following calculation
     * DIV = (CPU_FREQ / AHB_PRESCALAR / APBx_PRESCALAR)/(9600)
     * as we don't use the 8x oversampling */
    UART5->BRR = (SystemCoreClock
                    / 1     /* AHB DIV is 1 */
                    / 4)    /* APB1 DIV is 4 */
                    / 9600UL;
    UART5->CR1 |= USART_CR1_TE;
    while (1) {
        char buf[100];
/*         snprintf(buf,100,"%d %d %f\n",100,123,1.2F); */
        sprintf(buf,"%d %d %d\n",100,123,(int)(10000.0f*cosf(M_PI/4.)));
        puts(buf);
        int n;
        for (n = 0; n < 8000000; n++);
        GPIOG->ODR ^= (1 << 13);
    }
}
