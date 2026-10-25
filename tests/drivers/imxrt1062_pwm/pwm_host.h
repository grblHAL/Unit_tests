#pragma once
#include "grbl/hal.h"
#include "pwm.h"
#include "imxrt.h"
#include "check.h"
#include <string.h>
extern volatile uint32_t F_BUS_ACTUAL;
extern uint32_t pwm_mux[64];
void pwm_prepare(void);
