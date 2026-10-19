#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    settings.flags.g92_is_volatile = false;
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = incoming_controls;
    hal.stream.is_connected = incoming_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;
    char block1[] = "G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], -10.0f);
    NEAR(gc_state.g92_offset.coord.values[1], -20.0f);
    char block2[] = "G92.1";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], 0.0f);
    NEAR(gc_state.g92_offset.coord.values[1], 0.0f);

    return EXIT_SUCCESS;
}
