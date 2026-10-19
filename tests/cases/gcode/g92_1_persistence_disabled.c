#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    settings.flags.g92_is_volatile = false; // Persistence enabled
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // G92 X10 Y20 - Set G92 offset (persistent)
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset[0], -10.0f);
    NEAR(gc_state.g92_offset[1], -20.0f);

    // G92.1 - Reset G92 offset
    char block2[] = "G92.1";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset[0], 0.0f);
    NEAR(gc_state.g92_offset[1], 0.0f);

    // G92 with persistence disabled
    settings.flags.g92_is_volatile = true;
    char block3[] = "G92X5Y5";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.g92_offset[0], -5.0f);
    NEAR(gc_state.g92_offset[1], -5.0f);

    // G92.1 - Reset
    char block4[] = "G92.1";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.g92_offset[0], 0.0f);
    NEAR(gc_state.g92_offset[1], 0.0f);

    return EXIT_SUCCESS;
}