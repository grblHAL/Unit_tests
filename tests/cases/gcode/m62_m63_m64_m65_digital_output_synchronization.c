#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>

static unsigned digital_output_calls[8];
static void digital_output(void *port, bool state)
{
    uint_fast8_t idx = (uintptr_t)port;
    CHECK(idx < 8);
    digital_output_calls[idx]++;
}

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    // Register digital output ports
    for(unsigned i = 0; i < 4; i++) {
        hal.port.get_pin_info = NULL; // Not needed for this test
    }
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // Note: M62-M65 require I/O ports to be claimed and configured
    // This test verifies the parser accepts/rejects them correctly

    // Without claimed ports, M62 should fail
    char block1[] = "M62P0";
    CHECK(gc_execute_block(block1) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}