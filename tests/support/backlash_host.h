#pragma once
#include "support/motion_program_host.h"
static inline void prepare_backlash(void)
{
    prepare_motion_program();
    settings.axis[X_AXIS].backlash = .1f;
    mc_backlash_init((axes_signals_t){.bits = 1u << X_AXIS});
}
