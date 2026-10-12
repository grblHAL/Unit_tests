#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(delta_realtime_calls == 1);
    CHECK(strcmp(engine_output, "|Fixture:1") == 0);
    return EXIT_SUCCESS;
}
