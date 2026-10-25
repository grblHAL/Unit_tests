#include "support/ram_macro_motion_host.h"

int main(void)
{
    ram_prepare_assets = install_scoped_motion;
    run_ram_root_protocol(
        "#100=0\nG21G90\nO10IF[0]\n"
        "O20DO\nG1X99F100\n#100=99\nO20WHILE[0]\n"
        "O30REPEAT[3]\nG1X88F100\n#100=88\nO30ENDREPEAT\n"
        "O40WHILE[1]\nG1X77F100\n#100=77\nO40ENDWHILE\n"
        "O50IF[1]\nG1X66F100\n#100=66\n"
        "O50ELSE\nG1X55F100\n#100=55\nO50ENDIF\n"
        "O10ELSE\nG1X1F100\n#100=1\nO10ENDIF\nG4P0.01\n");
    NEAR(ram_flow_parameter(100), 1);
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(scoped_motion_services > 0 && !st_is_stepping());
    CHECK(plan_get_current_block() == NULL && sys.flags.exit && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
