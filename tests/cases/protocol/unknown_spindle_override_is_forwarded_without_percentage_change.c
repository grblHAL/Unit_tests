#include "support/protocol_host.h"
#include "check.h"
static unsigned unknown_calls; static uint8_t unknown_command;
static void capture_unknown(uint8_t command) { unknown_calls++; unknown_command = command; }
int main(void)
{
    prepare_protocol();
    unsigned before = gc_spindle_get(-1)->hal->param->override_pct;
    CHECK(grbl.on_unknown_accessory_override == NULL);
    enqueue_spindle_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(gc_spindle_get(-1)->hal->param->override_pct == before);
    CHECK(get_spindle_override() == 0 && unknown_calls == 0);
    grbl.on_unknown_accessory_override = capture_unknown;
    enqueue_spindle_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(unknown_calls == 1); CHECK(unknown_command == 0xEE);
    CHECK(gc_spindle_get(-1)->hal->param->override_pct == before);
    CHECK(get_spindle_override() == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_FINE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(gc_spindle_get(-1)->hal->param->override_pct == before + SPINDLE_OVERRIDE_FINE_INCREMENT);
    CHECK(unknown_calls == 1 && get_spindle_override() == 0);
    return EXIT_SUCCESS;
}
