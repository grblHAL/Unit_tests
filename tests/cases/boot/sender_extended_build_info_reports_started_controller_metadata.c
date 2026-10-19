#include "support/boot_host.h"
static void install_driver_information(settings_t *current)
{
    CHECK(current == &settings);
    hal.info = "Host driver";
    hal.board = "Fixture board";
}
int main(void)
{
    boot_during_setup = install_driver_information;
    boot_program = "$I+\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[VER:") != NULL);
    CHECK(strstr(engine_output, "[FIRMWARE:grblHAL]") != NULL);
    CHECK(strstr(engine_output, "[DRIVER:Host driver]") != NULL);
    CHECK(strstr(engine_output, "[BOARD:Fixture board]") != NULL);
    CHECK(strstr(engine_output, "[NVS STORAGE:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
