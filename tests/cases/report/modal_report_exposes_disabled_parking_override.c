#include "support/report_host.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    prepare_report(); settings.parking.flags.enable_override_control=true; sys.override.control.parking_disable=true;
    report_gcode_modes(hal.stream.write); CHECK(strstr(engine_output," M56 ")!=NULL);
    return EXIT_SUCCESS;
}
