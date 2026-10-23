#include "support/ram_macro_motion_host.h"
int main(void)
{
    ram_prepare_assets = install_scoped_motion;
    run_ram_macro_protocol(
        "#1=99\nG21G90\nG65P10A5\nG91G1X1F100\nG4P0.01\n#100=#1\n",
        "M73\nG20G91\nG1X0.0393700787F3.93700787\nG65P20A7\n#101=#1\n",
        "M73\nG21G90\nG1Y2F100\n#102=#1\n");
    CHECK(scoped_motion_services > 0 && wake_calls > 0 && !st_is_stepping());
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 160);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 160);
    CHECK(axis_pulses[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 2);
    NEAR(gc_state.position[Y_AXIS], 2);
    CHECK(!gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 100);
    NEAR(ram_flow_parameter(100), 99);
    NEAR(ram_flow_parameter(101), 5);
    NEAR(ram_flow_parameter(102), 7);
    for(unsigned i = 0; i < 3; i++)
        CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
