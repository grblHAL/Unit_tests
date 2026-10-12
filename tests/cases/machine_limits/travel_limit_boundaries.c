#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init(); sys.homed.mask = 1;
    work_envelope_t envelope = {.min.values = {-100, -100, -100}, .max.values = {0, 0, 0}};
    axes_signals_t axes = {.mask = 1}; float target[N_AXIS] = {-100, 999, 999};
    CHECK(grbl.check_travel_limits(target, axes, true, &envelope)); target[0] = 0; CHECK(grbl.check_travel_limits(target, axes, true, &envelope));
    target[0] = .01f; CHECK(!grbl.check_travel_limits(target, axes, true, &envelope));
    target[0] = -100.01f; CHECK(!grbl.check_travel_limits(target, axes, true, &envelope));
    return EXIT_SUCCESS;
}
