#include "support/boot_host.h"
#include "kinematics/interface.h"
static void provide_geometry_storage(void) { hal.nvs.type = NVS_EEPROM; }
int main(void)
{
    boot_during_init = provide_geometry_storage;
    boot_program = "M850\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(kinematics.transform_from_cartesian && kinematics.transform_steps_to_cartesian);
    CHECK(kinematics.segment_line);
    CHECK(setting_get_details(Setting_Kinematics0, NULL) != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
