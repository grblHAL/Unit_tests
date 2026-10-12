#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    primary_output[0] = pendant_output[0] = '\0';
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT));
    engine_execute_tasks(STATE_IDLE);
    CHECK(strncmp(pendant_output, "<Idle", 5) == 0);
    CHECK(primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
