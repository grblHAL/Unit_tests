#include "bltouch_host.h"
int main(void)
{
#ifdef TEST_TOOLSETTER
    native_toolsetter = true;
#else
    native_probe = true;
#endif
    load_bltouch();
    float target[N_AXIS] = {0};
    plan_line_data_t data = {0};
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    grbl.on_probe_completed();
    CHECK(starts == 1 && completed == 1 && outputs == 1 && angle == 90 && selections == 0);
    command_bltouch(Probe_Deploy);
    CHECK(angle == 10 && outputs == 2);
    return 0;
}
