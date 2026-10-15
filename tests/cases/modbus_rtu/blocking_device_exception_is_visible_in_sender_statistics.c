#include "support/rtu_exception_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    request_device_exception(1);
    char command[] = "$MODBUSSTATS";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "RX exceptions: 1") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 0") != NULL);
    CHECK(exceptions == 1 && exception_code == 1);
    return EXIT_SUCCESS;
}
