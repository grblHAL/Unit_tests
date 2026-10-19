#include "support/incoming_gcode_host.h"
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
    settings.coolant.on_delay = 100;
    hal.control.get_state = incoming_controls;
    hal.stream.is_connected = incoming_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;
    CHECK(incoming_block("M7") == Status_OK);
    CHECK(coolant_state.mist == On);

    CHECK(incoming_block("M8") == Status_OK);
    CHECK(coolant_state.flood == On);

    CHECK(incoming_block("M9") == Status_OK);
    CHECK(coolant_state.value == 0);
    CHECK(incoming_block("M7") == Status_OK);
    CHECK(coolant_state.mist == On);
    CHECK(incoming_block("M9") == Status_OK);
    CHECK(coolant_state.mist == Off);
    CHECK(incoming_block("M8") == Status_OK);
    CHECK(coolant_state.flood == On);
    CHECK(incoming_block("M9") == Status_OK);
    CHECK(coolant_state.flood == Off);

    return EXIT_SUCCESS;
}
