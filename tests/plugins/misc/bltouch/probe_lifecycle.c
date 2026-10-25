#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    settings.probe.probe2_auto_select = On;
    float target[N_AXIS] = {0};
    plan_line_data_t data = {0};
    CHECK(grbl.on_probe_start((axes_signals_t){.mask = 4}, target, &data));
    CHECK(starts == 1 && angle == 10 && selected_probe == Probe_2 && selections == 1);
    grbl.on_probe_completed();
    CHECK(completed == 1 && angle == 90 && selected_probe == Probe_Default && selections == 2);
    return 0;
}
