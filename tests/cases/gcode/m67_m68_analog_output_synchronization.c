#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>

static unsigned analog_output_calls[8];
static void analog_output(void *port, float value)
{
    uint_fast8_t idx = (uintptr_t)port;
    CHECK(idx < 8);
    analog_output_calls[idx]++;
}

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // Without claimed ports, M67/M68 should fail
    char block1[] = "M67E0Q1.0";
    CHECK(gc_execute_block(block1) == Status_GcodeUnsupportedCommand);

    char block2[] = "M68E0Q1.0";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}