#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

static int macro_calls = 0;
static status_code_t macro_exec(sys_state_t state, parser_block_t *gc_block)
{
    (void)state; (void)gc_block;
    macro_calls++;
    return Status_OK;
}

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    grbl.on_macro_execute = macro_exec;
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // Set initial modal state
    char block1[] = "G90G94G17";
    CHECK(gc_execute_block(block1) == Status_OK);

    // M70 - Save modal state
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G66 modal macro
    char block3[] = "G66P100";
    CHECK(gc_execute_block(block3) == Status_OK);

    // X10 - Should call macro
    char block4[] = "X10";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(macro_calls == 1);

    // M72 - Restore modal state (should cancel G66)
    char block5[] = "M72";
    CHECK(gc_execute_block(block5) == Status_OK);
    CHECK(gc_state.modal.macro_id == 0);

    // X20 - Should not call macro
    char block6[] = "X20";
    CHECK(gc_execute_block(block6) == Status_OK);
    CHECK(macro_calls == 1);

    return EXIT_SUCCESS;
}