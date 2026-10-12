#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    send_request(); inject_reply(true); poll_rtu();
    char command[] = "$MODBUSSTATS";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 1") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 1") != NULL);
    CHECK(strstr(engine_output, "timeouts: 0") != NULL);
    return EXIT_SUCCESS;
}
