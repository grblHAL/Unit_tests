#pragma once
// Cortex interrupt operations are host callbacks; peripheral types remain original SDK types.
#define __IO volatile
#define __I volatile const
#define __O volatile
void NVIC_EnableIRQ(IRQn_Type irq);
void NVIC_SetPriority(IRQn_Type irq, uint32_t priority);
