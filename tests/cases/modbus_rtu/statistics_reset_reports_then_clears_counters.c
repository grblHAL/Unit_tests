#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    send_request(); inject_reply(false); poll_rtu();
    char reset[] = "$MODBUSSTATS=R";
    CHECK(system_execute_line(reset, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 1") != NULL);
    engine_output[0] = '\0';
    char report[] = "$MODBUSSTATS";
    CHECK(system_execute_line(report, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 0") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 0") != NULL);
    return EXIT_SUCCESS;
}
