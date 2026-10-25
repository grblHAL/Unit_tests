#pragma once
#include "driver.h"
// The real device/board headers stay intact; only CPU interrupt intrinsics are host calls.
#undef __enable_interrupts
#undef __disable_interrupts
void msp_irq_enable(void);
void msp_irq_disable(void);
#define __enable_interrupts() msp_irq_enable()
#define __disable_interrupts() msp_irq_disable()
