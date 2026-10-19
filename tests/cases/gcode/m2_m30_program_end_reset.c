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

    // M2 - Program end
    char block1[] = "G1X10F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);

    char block2[] = "M2";
    CHECK(gc_execute_block(block2) == Status_OK);
    // Program should end, state should be reset
    CHECK(state_get() == STATE_IDLE);
    // Modal state should be reset
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    CHECK(gc_state.modal.coolant.value == 0);
    CHECK(gc_state.tool == 0);

    // M30 - Program end with rewind
    char block3[] = "G1X20F100";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 20.0f);

    char block4[] = "M30";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(state_get() == STATE_IDLE);
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    CHECK(gc_state.modal.coolant.value == 0);

    return EXIT_SUCCESS;
}