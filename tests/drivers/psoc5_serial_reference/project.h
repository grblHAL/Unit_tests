#pragma once
#include <stdint.h>
/* Generated PSoC UART boundary declarations; no Cypress SDK build is claimed. */
void UART_Start(void);
void UART_RX_Interrupt_StartEx(void (*handler)(void));
void UART_PutChar(uint8_t value);
uint8_t UART_GetChar(void);
void UART_ClearRxBuffer(void);
