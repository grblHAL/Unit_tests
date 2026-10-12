#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(stream_mpg_check_enable(CMD_MPG_MODE_TOGGLE));
    CHECK(!sys.mpg_mode);
    engine_execute_tasks(STATE_IDLE);
    CHECK(sys.mpg_mode);
    CHECK(hal.stream.read == pendant_input);
    CHECK(stream_mpg_enable(false));
    return EXIT_SUCCESS;
}
