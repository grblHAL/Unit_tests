#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    settings.status_report.probe_coordinates = true;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(strstr(engine_output, "[PRB:0.500,0.000,0.000:1]") != NULL);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
