#include "support/report_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"
static unsigned realtime_calls;
static uint8_t realtime_byte;
static bool custom_realtime(uint8_t byte) { realtime_calls++; realtime_byte = byte; return false; }

int main(void)
{
    prepare_report();
    hal.stream.enqueue_rt_command = custom_realtime;
    CHECK(!stream_enqueue_realtime_command('X'));
    CHECK(realtime_calls == 1 && realtime_byte == 'X');
    CHECK(sys.rt_exec_state == 0);
    return EXIT_SUCCESS;
}
