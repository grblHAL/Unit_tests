#include "input_host.h"
static void high(void)
{
    sample = 1;
    poll_action = NULL;
}
static void low(void)
{
    sample = 0;
    poll_action = NULL;
}
int main(void)
{
    start_inputs();
    poll_action = high;
    CHECK(ports.wait_on_input(0, WaitMode_High, 0.1f) == 1);
    CHECK(polls > 0 && delays > 0);
    unsigned before = polls;
    poll_action = low;
    CHECK(ports.wait_on_input(0, WaitMode_Low, 0.1f) == 0 && polls > before);
    before = polls;
    CHECK(ports.wait_on_input(0, WaitMode_Low, 0.1f) == 0 && polls == before);
    return 0;
}
