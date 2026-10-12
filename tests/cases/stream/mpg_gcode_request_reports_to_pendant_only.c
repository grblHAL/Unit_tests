#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    primary_output[0] = pendant_output[0] = '\0';
    CHECK(stream_mpg_check_enable(CMD_GCODE_REPORT));
    CHECK(pendant_output[0] == '\0');
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
