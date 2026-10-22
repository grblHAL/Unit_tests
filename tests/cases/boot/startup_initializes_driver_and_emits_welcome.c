#include "support/boot_host.h"
#include "check.h"
#include "spindle_control.h"

int main(void)
{
    boot_program = "$G\n$SPINDLES\n$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "GrblHAL 1.1f") != NULL);
    CHECK(sys.driver_started);
    CHECK(spindle_get_count() == 0);
    CHECK(strstr(engine_output, "No spindles registered." ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
