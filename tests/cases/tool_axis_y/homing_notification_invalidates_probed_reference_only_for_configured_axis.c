#include "support/fixed_axis_probe_reference_host.h"

int main(void)
{
    probe_then_set_fixed_axis_reference();
    hal.stream.report.flags.value = 0;
    const uint8_t unrelated_axis = (TOOL_LENGTH_OFFSET_AXIS + 1) % N_AXIS;
    system_clear_tlo_reference((axes_signals_t){.mask = bit(unrelated_axis)});
    CHECK(sys.tlo_reference_set.mask == bit(TOOL_LENGTH_OFFSET_AXIS));
    CHECK(!(hal.stream.report.flags.value & Report_TLOReference));
    system_clear_tlo_reference((axes_signals_t){.mask = bit(TOOL_LENGTH_OFFSET_AXIS)});
    CHECK(sys.tlo_reference_set.mask == 0);
    CHECK(hal.stream.report.flags.value & Report_TLOReference);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
