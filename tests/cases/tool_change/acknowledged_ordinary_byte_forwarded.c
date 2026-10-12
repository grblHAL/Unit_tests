#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    grbl.on_toolchange_ack();
    CHECK(!tool_stream_handler('G'));
    CHECK(forwarded_bytes == 1 && forwarded_byte == 'G');
    return EXIT_SUCCESS;
}
