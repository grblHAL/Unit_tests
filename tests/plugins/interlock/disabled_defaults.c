#include "interlock_host.h"
int main(void)
{
    il_start();
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 0);
    hal.port.digital_out(1, true);
    CHECK(hardware_outputs == 1 && output_value);
    CHECK(saves == 1);
    return 0;
}
