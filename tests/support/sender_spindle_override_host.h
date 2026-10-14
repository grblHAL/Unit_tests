#pragma once
#include "support/spindle_override_host.h"
static inline spindle_ptrs_t *prepare_sender_spindle_override(void)
{
    prepare_multi_spindle_program();
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->update_rpm = override_rpm_output;
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    grbl.on_override_changed = override_event;
    return spindle;
}
static inline void send_spindle_override(uint8_t command)
{
    CHECK(protocol_enqueue_realtime_command(command));
    CHECK(protocol_exec_rt_system());
    NEAR(gc_spindle_get(0)->rpm, 5000);
    CHECK(gc_spindle_get(0)->state.on);
}
