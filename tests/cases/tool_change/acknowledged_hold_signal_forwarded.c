#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    grbl.on_toolchange_ack();
    hal.control.interrupt_callback((control_signals_t){.feed_hold = true});
    CHECK(forwarded_controls == 1 && forwarded_signals.feed_hold);
    return EXIT_SUCCESS;
}
