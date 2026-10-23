#include "support/ram_macro_motion_host.h"
int main(void)
{
    ram_prepare_assets = install_scoped_motion;
    // The sender queries after the file error before issuing its recovery cut.
    ram_sender_query = "$G\nG1X2F100\nG4P0.01\n$G\n";
    run_ram_macro_protocol("#1=3\nG65P10A5\nG91\n",
        "#1=9\nG1X1F100\nG65P20A7\nG20\n",
        "#1=17\nG1Y1F100\nG999\nG18\n");
    for(unsigned i = 0; i < 3; i++) {
        CHECK(ram_macro_errors[i] >= 1);
        CHECK(ram_return_status[i] == Status_GcodeUnsupportedCommand);
    }
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.last_error == Status_OK); /* Restored sender query succeeds. */
    float parent; CHECK(ngc_param_get(1, &parent)); NEAR(parent, 3);
    CHECK(scoped_motion_services > 0 && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 0 && !st_is_stepping());
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
