#include "support/engine_host.h"
#include "coolant_control.h"
#include "check.h"
#include <string.h>

static coolant_state_t coolant_state;
static void coolant_set(coolant_state_t s) { coolant_state = s; }
static coolant_state_t coolant_get(void) { return coolant_state; }

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.coolant.set_state = coolant_set;
    hal.coolant.get_state = coolant_get;
    hal.coolant_cap.mist = true;
    hal.coolant_cap.flood = true;
    hal.coolant_cap.delay = 100;
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // M7 - Mist coolant on
    char block1[] = "M7";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(coolant_state.mist == On);

    // M8 - Flood coolant on
    char block2[] = "M8";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(coolant_state.flood == On);
    CHECK(coolant_state.mist == On); // Both can be on

    // M9 - Coolant off
    char block3[] = "M9";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(coolant_state.value == 0);

    return EXIT_SUCCESS;
}