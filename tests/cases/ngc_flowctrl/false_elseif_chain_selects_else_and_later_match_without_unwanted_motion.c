#include "support/ram_macro_motion_host.h"

int main(void)
{
    ram_prepare_assets = install_scoped_motion;
    run_ram_root_protocol(
        "#100=0\n#101=0\nG21G90\n"
        "O10IF[#100GT10]\nG1X99F100\n#101=99\n"
        "O10ELSEIF[#100GT5]\nG1X88F100\n#101=88\n"
        "O10ELSEIF[#100GT2]\nG1X77F100\n#101=77\n"
        "O10ELSE\nG1X1F100\n#101=1\nO10ENDIF\n"
        "#100=8\n"
        "O20IF[#100GT10]\nG1X66F100\n#101=66\n"
        "O20ELSEIF[#100LT5]\nG1X55F100\n#101=55\n"
        "O20ELSEIF[#100GT5]\nG1X2F100\n#101=[#101+1]\n"
        "O20ELSE\nG1X44F100\n#101=44\nO20ENDIF\nG4P0.01\n");
    NEAR(ram_flow_parameter(100), 8);
    NEAR(ram_flow_parameter(101), 2);
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 2);
    CHECK(scoped_motion_services > 0 && !st_is_stepping());
    CHECK(plan_get_current_block() == NULL && sys.flags.exit && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
