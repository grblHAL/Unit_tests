#include "support/report_host.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    prepare_report(); sys.override.control.feed_hold_disable=true; report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output," M53 ")!=NULL);
    return EXIT_SUCCESS;
}
