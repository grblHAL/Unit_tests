#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    probe_ok = false;
    float target[N_AXIS] = {0};
    plan_line_data_t data = {0};
    CHECK(!grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(starts == 1 && angle == 90 && outputs == 1 && selections == 0);
    return 0;
}
