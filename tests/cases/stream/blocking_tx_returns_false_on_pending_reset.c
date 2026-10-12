#include "support/stream_blocking_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_blocking();
    sys.rt_exec_state = EXEC_RESET;
    CHECK(!stream_tx_blocking());
    CHECK(blocking_callbacks == 1 && !nested_result);
    return EXIT_SUCCESS;
}
