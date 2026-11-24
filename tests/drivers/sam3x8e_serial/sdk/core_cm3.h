#pragma once
// Cortex interrupt operations are host callbacks; peripheral types remain original SDK types.
#define __IO volatile
#define __I volatile const
#define __O volatile
void __disable_irq(void);
void __enable_irq(void);
void __DMB(void);
void NVIC_EnableIRQ(IRQn_Type irq);
void NVIC_SetPriority(IRQn_Type irq, uint32_t priority);
