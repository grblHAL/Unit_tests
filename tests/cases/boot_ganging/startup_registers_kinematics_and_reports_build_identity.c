#include "support/boot_host.h"
#include "kinematics/interface.h"
#include "check.h"

int main(void)
{
    boot_program = "$I\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(sys.driver_started);
    CHECK(kinematics.transform_from_cartesian != NULL);
    CHECK(kinematics.transform_steps_to_cartesian != NULL);
    CHECK(kinematics.segment_line != NULL);
    CHECK(strstr(engine_output, "[KINEMATICS:Asymmetric ganging v0.02]") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
