#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_param_t param = {0};
    spindle_ptrs_t spindle = {.rpm_min = 1000, .rpm_max = 12000, .param = &param};
    NEAR(spindle_set_rpm(&spindle, 15000, 100), 12000);
    return EXIT_SUCCESS;
}
