#pragma once
#include "support/probe_motion_host.h"
static int32_t explicit_toolsetter_contact = 64, explicit_second_contact = 56;
static probe_id_t explicit_start_probe;
static unsigned explicit_start_calls, explicit_selection_calls;
static bool (*explicit_original_select)(probe_id_t id);
static bool explicit_contact_input(void *input) { return sys.position[X_AXIS] >= *(int32_t *)input; }
static bool explicit_select(probe_id_t id)
{
    explicit_selection_calls++;
    return explicit_original_select(id);
}
static bool explicit_probe_start(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    (void)data;
    CHECK(axes.mask == X_AXIS_BIT);
    NEAR(target[X_AXIS], 1);
    explicit_start_probe = hal.probe.get_state().probe_id;
    explicit_start_calls++;
    return true;
}
static inline void prepare_explicit_probe(void)
{
    prepare_probe_motion();
    CHECK(probe_add(Probe_Toolsetter, 1, IRQ_Mode_None, &explicit_toolsetter_contact, explicit_contact_input));
    CHECK(probe_add(Probe_2, 2, IRQ_Mode_None, &explicit_second_contact, explicit_contact_input));
    hal.driver_cap.probe = hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    explicit_original_select = hal.probe.select;
    hal.probe.select = explicit_select;
    grbl.on_probe_start = explicit_probe_start;
}
static inline status_code_t explicit_probe_block(const char *text)
{
    char block[64];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
static inline void check_explicit_contact(probe_id_t selected, probe_id_t restored, int32_t contact)
{
    CHECK(explicit_start_calls == 1 && explicit_start_probe == selected);
    CHECK(hal.probe.get_state().probe_id == restored);
    CHECK(completed_calls == 1 && sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] >= contact && sys.probe_position[X_AXIS] <= contact + 2);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    NEAR(gc_state.position[X_AXIS], (float)physical_position[X_AXIS] / settings.axis[X_AXIS].steps_per_mm);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
}
