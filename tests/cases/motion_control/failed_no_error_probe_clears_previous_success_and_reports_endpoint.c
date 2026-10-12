#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    sys.flags.probe_succeeded = true;
    contact_steps = 1000;
    settings.status_report.probe_coordinates = true;
    CHECK(probe_to_one_mm((gc_parser_flags_t){.probe_is_no_error=true}) == GCProbe_FailEnd);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(strstr(engine_output, "[PRB:1.000,0.000,0.000:0]") != NULL);
    CHECK(sys.probing_state == Probing_Off);
    CHECK(!hal.probe.get_state().is_probing);
    return EXIT_SUCCESS;
}
