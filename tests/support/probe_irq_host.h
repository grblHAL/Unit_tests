#pragma once
#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool irq_input;
static bool irq_accept = true;
static pin_irq_mode_t installed_mode;
static ioport_interrupt_callback_ptr installed_callback;
static unsigned control_calls;
static control_signals_t captured_control;
static bool irq_read_input(void *input) { return *(bool *)input; }
static bool install_probe_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(port == 0);
    installed_mode = mode;
    installed_callback = callback;
    return irq_accept;
}
static control_signals_t control_state(void)
{
    return (control_signals_t){.feed_hold = true};
}
static void capture_control(control_signals_t state)
{
    captured_control = state;
    control_calls++;
}
static inline void prepare_probe_irq(void)
{
    engine_prepare();
    hal.port.register_interrupt_handler = install_probe_irq;
    hal.control.get_state = control_state;
    hal.control.interrupt_callback = capture_control;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_RisingFalling | IRQ_Mode_Change,
                    &irq_input, irq_read_input));
}
