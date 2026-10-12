#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    away_contact = true;
    CHECK(probe_to_one_mm((gc_parser_flags_t){.probe_is_away = true}) == GCProbe_Found);
    CHECK(sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
