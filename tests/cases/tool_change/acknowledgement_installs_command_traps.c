#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler != original_enqueue);
    CHECK(hal.control.interrupt_callback != original_control);
    CHECK(stream_handler_changes == 1);
    return EXIT_SUCCESS;
}
