#include "support/engine_host.h"
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

    // G66 modal macro
    char block1[] = "G66P100";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G66 again - should fail (already active)
    char block2[] = "G66P100";
    CHECK(gc_execute_block(block2) == Status_GcodeModalGroupViolation);

    // G66.1 while G66 active - should fail
    char block3[] = "G66.1P101";
    CHECK(gc_execute_block(block3) == Status_GcodeModalGroupViolation);

    // G67 to cancel
    char block4[] = "G67";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G66.1 after G67
    char block5[] = "G66.1P101";
    CHECK(gc_execute_block(block5) == Status_OK);

    // G66 after G66.1 - should fail
    char block6[] = "G66P100";
    CHECK(gc_execute_block(block6) == Status_GcodeModalGroupViolation);

    // G66.1 again - should fail
    char block7[] = "G66.1P101";
    CHECK(gc_execute_block(block7) == Status_GcodeModalGroupViolation);

    return EXIT_SUCCESS;
}