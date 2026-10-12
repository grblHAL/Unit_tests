#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_param_t param = {0};
    spindle_ptrs_t spindle = {.rpm_min = 1000, .rpm_max = 12000, .param = &param};
    CHECK(fabsf(spindle_set_rpm(&spindle, 5000, 120) - 6000) < .01f);
    CHECK(fabsf(param.rpm_overridden - 6000) < .01f);
    CHECK(param.override_pct == 120);
    return EXIT_SUCCESS;
}
