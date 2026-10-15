#include "support/rtu_blocking_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1);
    CHECK(!send_blocking_request(0));
    CHECK(tx_calls == 2 && exceptions == 1);
    char command[] = "$MODBUSSTATS";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "Unstable connection to modbus device?") != NULL);
    CHECK(strstr(engine_output, "timeouts: 1") != NULL);
    return EXIT_SUCCESS;
}
