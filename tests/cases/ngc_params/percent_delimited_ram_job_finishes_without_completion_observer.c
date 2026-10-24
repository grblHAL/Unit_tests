#include "support/ram_macro_motion_host.h"

static void prepare_percent_job(void)
{
    install_scoped_motion();
    CHECK(grbl.on_program_completed == NULL);
}

int main(void)
{
    ram_prepare_assets = prepare_percent_job;
    run_ram_root_protocol("%\nG21G90G1X1F100\n%\n");
    CHECK(grbl.on_program_completed == NULL);
    CHECK(scoped_motion_services > 0 && wake_calls > 0);
    CHECK(!st_is_stepping() && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 80);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(strstr(engine_output, "[MSG:Pgm End]") != NULL);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
