#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.register_interrupt_handler(0, 37, IRQ_Mode_Change, flex_event));
    flex_run();
    const wait_mode_t modes[] = {WaitMode_Rise, WaitMode_Fall, WaitMode_High, WaitMode_Low};
    for (unsigned i = 0; i < sizeof(modes) / sizeof(modes[0]); i++)
    {
        flex_irq(modes[i] == WaitMode_Low ? 1U << 3 : 0);
        unsigned before_rt = realtime_calls, before_delay = delay_calls;
        abort_on_realtime = true;
        CHECK(bank.wait_on_input(0, modes[i], 60.0f) == -1);
        CHECK(sys.abort && realtime_calls == before_rt + 1 && delay_calls == before_delay + 1);
        abort_on_realtime = false;
        sys.abort = false;
        unsigned before_events = events;
        flex_irq(input_bits ^ (1U << 3));
        CHECK(events == before_events + 1 && event_port == 37);
    }
    CHECK(alarms == 0);
    return 0;
}
