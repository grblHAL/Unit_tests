#include "support/engine_host.h"
#include "check.h"
#include <string.h>

static bool probe_state = false;
static limit_signals_t probe_signals;

static limit_signals_t limits(void) { return probe_signals; }

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset());
    hal.limits.get_state = limits;
    hal.limits.enable = enable_limits;
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // G38.2 - Probe toward workpiece, stop on contact, error if no contact
    probe_signals = (limit_signals_t){.min = 0, .max = 0};
    char block1[] = "G38.2X10F100";
    CHECK(gc_execute_block(block1) == Status_OK);

    // Trigger probe
    probe_signals.min = 1;
    // Probe should stop and record position
    // This is a simplified test - actual probing requires stepper execution

    // G38.3 - Probe toward workpiece, stop on contact
    probe_signals = (limit_signals_t){.min = 0, .max = 0};
    char block2[] = "G38.3X20F100";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G38.4 - Probe away from workpiece, stop on loss of contact
    probe_signals = (limit_signals_t){.min = 1, .max = 0};
    char block3[] = "G38.4X0F100";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G38.5 - Probe away from workpiece, stop on loss of contact
    probe_signals = (limit_signals_t){.min = 1, .max = 0};
    char block4[] = "G38.5X0F100";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}