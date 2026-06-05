#include "USART.h"

#include <stdint.h>

void EnableUSART1(void)
{
    USART1_CR1 |= USART_CR1_UE_BIT;
}

void DisableUSART1(void)
{
    USART1_CR1 &= ~USART_CR1_UE_BIT;
}

uint8_t ReadUSART1(void)
{
    return (uint8_t)(USART1_DR & (uint8_t)0xFF);
}

void WriteUSART1(uint8_t Data)
{
    USART1_DR = ((uint32_t)(Data)) & ((uint32_t)0x000000FF);
}

void USART1ClearFlag(uint16_t Flag)
{
    USART1_SR = (uint16_t)(~Flag);
}