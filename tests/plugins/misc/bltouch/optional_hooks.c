#include "bltouch_host.h"
int main(void)
{
    no_previous_probe_hooks = true;
    load_bltouch();
    float target[N_AXIS] = {0};
    plan_line_data_t data = {0};
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(angle == 10 && outputs == 2 && starts == 0);
    grbl.on_probe_completed();
    CHECK(angle == 90 && outputs == 3 && completed == 0);
    return 0;
}
