#include "input_host.h"
static void changed(uint8_t port, bool value)
{
    (void)port;
    (void)value;
    CHECK(false);
}
int main(void)
{
    start_inputs();
    unsigned before = sends;
    CHECK(!ports.register_interrupt_handler(0, 7, IRQ_Mode_Change, changed));
    CHECK(ports.wait_on_input(0, WaitMode_Rise, 0.1f) == -1);
    CHECK(ports.wait_on_input(INPUT_COUNT - 1, WaitMode_Fall, 0.1f) == -1);
    CHECK(ports.wait_on_input(INPUT_COUNT, WaitMode_Immediate, 0) == -1);
    CHECK(reads == 1 && sends == before);
    return 0;
}
