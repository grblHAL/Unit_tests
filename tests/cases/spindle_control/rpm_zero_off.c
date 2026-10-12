#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_param_t param = {0};
    spindle_ptrs_t spindle = {.rpm_min = 1000, .rpm_max = 12000, .param = &param};
    CHECK(spindle_set_rpm(&spindle, 0, 100) == 0);
    CHECK(spindle_set_rpm(&spindle, -100, 100) == 0);
    return EXIT_SUCCESS;
}
