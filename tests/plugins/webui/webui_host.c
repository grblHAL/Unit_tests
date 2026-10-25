#include "webui_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}

bool stream_await_tx_clear(const io_stream_t *stream)
{
    (void)stream;
    CHECK(false);
    return false;
}
