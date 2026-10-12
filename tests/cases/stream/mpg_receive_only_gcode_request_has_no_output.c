#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, true, stream_mpg_check_enable));
    CHECK(stream_mpg_check_enable(CMD_GCODE_REPORT));
    engine_execute_tasks(STATE_IDLE);
    CHECK(pendant_output[0] == '\0');
    return EXIT_SUCCESS;
}
