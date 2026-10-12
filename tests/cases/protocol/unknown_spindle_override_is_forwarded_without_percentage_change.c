#include "support/protocol_host.h"
#include "check.h"
static unsigned unknown_calls; static uint8_t unknown_command;
static void capture_unknown(uint8_t command) { unknown_calls++; unknown_command = command; }
int main(void)
{
    prepare_protocol(); grbl.on_unknown_accessory_override = capture_unknown;
    unsigned before = gc_spindle_get(-1)->hal->param->override_pct;
    enqueue_spindle_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(unknown_calls == 1); CHECK(unknown_command == 0xEE);
    CHECK(gc_spindle_get(-1)->hal->param->override_pct == before);
    CHECK(get_spindle_override() == 0);
    return EXIT_SUCCESS;
}
