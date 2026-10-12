#include "support/engine_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"
static unsigned null_handler_calls;
static uint8_t null_handler_byte;
static bool custom_null_realtime(uint8_t byte) { null_handler_calls++; null_handler_byte = byte; return true; }

int main(void)
{
    engine_prepare();
    const io_stream_t *stream = stream_null_init(115200);
    enqueue_realtime_command_ptr original = stream->set_enqueue_rt_handler(custom_null_realtime);
    CHECK(original == protocol_enqueue_realtime_command);
    CHECK(stream->set_enqueue_rt_handler(NULL) == custom_null_realtime);
    CHECK(stream->enqueue_rt_command('X'));
    CHECK(null_handler_calls == 1 && null_handler_byte == 'X');
    CHECK(stream->set_enqueue_rt_handler(original) == custom_null_realtime);
    CHECK(stream->enqueue_rt_command(CMD_STATUS_REPORT));
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
