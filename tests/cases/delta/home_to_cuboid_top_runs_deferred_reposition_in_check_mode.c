#include "support/delta_api_host.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
    CHECK(plan_reset());
    report_init_fns();
    report_init();
    state_set(STATE_CHECK_MODE);
    CHECK(delta_store(Setting_Kinematics7, "1") == Status_OK);
    grbl.on_homing_completed((axes_signals_t){.mask = 7}, true);
    NEAR(sys.home_position[Z_AXIS], sys.work_envelope.max.z);
    engine_execute_tasks(STATE_CHECK_MODE);
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.position[0] == 0 && sys.position[1] == 0 && sys.position[2] == 0);
    CHECK(delta_homing_calls == 1);
    return EXIT_SUCCESS;
}
