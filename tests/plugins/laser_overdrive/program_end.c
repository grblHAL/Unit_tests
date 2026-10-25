#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    CHECK(ovd_command(25, true) == Status_OK);
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!spindle_get(0)->context.pwm->flags.laser_off_overdrive && ovd_completions == 1);
    CHECK(ovd_command(12.5f, true) == Status_OK);
    grbl.on_program_completed(ProgramFlow_CompletedM2, true);
    CHECK(!spindle_get(0)->context.pwm->flags.laser_off_overdrive && ovd_completions == 2);
    return 0;
}
