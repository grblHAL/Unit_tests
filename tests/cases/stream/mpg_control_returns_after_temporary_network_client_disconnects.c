#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream(); CHECK(stream_mpg_register(&pendant_device,false,NULL));
    CHECK(stream_mpg_enable(true)); CHECK(sys.mpg_mode);
    CHECK(stream_connect(&secondary_connection)); CHECK(!sys.mpg_mode);
    CHECK(hal.stream.write == secondary_write);
    stream_disconnect(&secondary_connection);
    CHECK(!sys.mpg_mode && hal.stream.write == primary_write);
    engine_execute_tasks(STATE_IDLE);
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg && hal.stream.write == write_pendant);
    CHECK(stream_mpg_enable(false));
    return EXIT_SUCCESS;
}
