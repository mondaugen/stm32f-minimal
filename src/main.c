/* Minimal program */
#include "stm32f4xx.h" 

int main (void)
{
    /* Enable PORT G clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    /* Set mode to output */
    GPIOG->MODER |= (1 << (13*2));
    /* Set pin high */
    GPIOG->ODR |= (1 << 13);
    while (1);
}
