#include "support/engine_host.h"
#include "check.h"
#include <string.h>

static int macro_calls = 0;
static status_code_t macro_exec(sys_state_t state, parser_block_t *gc_block)
{
    (void)state;
    macro_calls++;
    // Check arguments
    if(gc_block->values.a == 1.0f && gc_block->values.b == 2.0f) {
        return Status_OK;
    }
    return Status_GcodeUnsupportedCommand;
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

    // G65 P100 A1 B2 - Call macro 100 with arguments
    char block1[] = "G65P100A1B2";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(macro_calls == 1);

    // G65 with local parameters
    char block2[] = "G65P101A10B20";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(macro_calls == 2);

    return EXIT_SUCCESS;
}