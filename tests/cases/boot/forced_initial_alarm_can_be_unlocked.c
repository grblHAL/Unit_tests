#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_force_alarm = true;
    boot_program = "$X\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started);
    CHECK(strstr(engine_output, "[MSG:'$H'|'$X' to unlock]") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
