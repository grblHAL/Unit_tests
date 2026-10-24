#pragma once
#include <stdint.h>
extern volatile uint32_t F_BUS_ACTUAL;
volatile uint32_t *portConfigRegister(uint8_t pin);
