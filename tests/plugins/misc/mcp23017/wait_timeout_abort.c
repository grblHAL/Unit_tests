#include "input_host.h"
static void abort_wait(void)
{
    sys.abort = true;
    poll_action = NULL;
}
int main(void)
{
    start_inputs();
    CHECK(ports.wait_on_input(0, WaitMode_High, 0.1f) == -1);
    CHECK(polls > 0 && polls < 16 && delays == polls);
    unsigned before = polls;
    poll_action = abort_wait;
    CHECK(ports.wait_on_input(0, WaitMode_High, 0.5f) == -1);
    CHECK(sys.abort && polls == before + 1 && delays == polls);
    return 0;
}
