#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>

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

    // M0 - Program pause
    char block1[] = "G1X10F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);

    char block2[] = "M0";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(state_get() == STATE_HOLD);

    // Resume with cycle start (simulated)
    sys.flags.hold = false;
    state_set(STATE_CYCLE);

    char block3[] = "G1X20F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 20.0f);

    // M1 - Optional program pause (requires optional stop switch)
    // With switch disabled, should continue
    sys.flags.optional_stop_disable = true;
    char block4[] = "G1X30F100";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 30.0f);

    char block5[] = "M1";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(state_get() == STATE_CYCLE); // Should not pause

    // With switch enabled, should pause
    sys.flags.optional_stop_disable = false;
    char block6[] = "G1X40F100";
    CHECK(gc_execute_block(block6) == Status_OK);
    NEAR(gc_state.position[0], 40.0f);

    char block7[] = "M1";
    CHECK(gc_execute_block(block7) == Status_OK);
    CHECK(state_get() == STATE_HOLD);

    return EXIT_SUCCESS;
}