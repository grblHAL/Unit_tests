#include "support/boot_host.h"
#include "kinematics/interface.h"
#include "check.h"

/* Delta stores geometry in the driver-provided physical NVS area. */
static void provide_geometry_storage(void) { hal.nvs.type = NVS_EEPROM; }

int main(void)
{
    boot_during_init = provide_geometry_storage;
    boot_program = "$I\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(sys.driver_started);
    CHECK(kinematics.transform_from_cartesian != NULL);
    CHECK(kinematics.transform_steps_to_cartesian != NULL);
    CHECK(kinematics.segment_line != NULL);
    CHECK(strstr(engine_output, "[KINEMATICS:Delta v0.06]") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
