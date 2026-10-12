#include "support/probe_irq_host.h"
static unsigned irq_calls;
static uint8_t irq_ports[4];
static pin_irq_mode_t irq_modes[4];
static bool trace_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(callback != NULL && irq_calls < 4);
    irq_ports[irq_calls] = port;
    irq_modes[irq_calls++] = mode;
    return true;
}

int main(void)
{
    prepare_probe_irq();
    hal.port.register_interrupt_handler = trace_irq;
    bool second = false;
    CHECK(probe_add(Probe_2, 1, IRQ_Mode_RisingFalling | IRQ_Mode_Change, &second, irq_read_input));
    settings.probe.enable_protection = true;
    hal.probe.configure(false, false);
    CHECK(irq_calls == 1 && irq_ports[0] == 0 && irq_modes[0] == IRQ_Mode_Change);
    CHECK(hal.probe.select(Probe_2));
    CHECK(irq_calls == 3);
    CHECK(irq_ports[1] == 0 && irq_modes[1] == IRQ_Mode_None);
    CHECK(irq_ports[2] == 1 && irq_modes[2] == IRQ_Mode_Change);
    CHECK(hal.probe.get_state().probe_id == Probe_2);
    CHECK(hal.probe.get_caps(Probe_2).guarded);
    return EXIT_SUCCESS;
}
