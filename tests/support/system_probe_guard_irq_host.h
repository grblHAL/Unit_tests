#pragma once
#include "support/system_command_host.h"
#include "probe.h"
static bool guard_probe_input;
static unsigned guard_irq_installs;
static pin_irq_mode_t guard_irq_mode;
static ioport_interrupt_callback_ptr guard_irq_callback;
static bool guard_read_input(void *input) { CHECK(input == &guard_probe_input); return guard_probe_input; }
static bool guard_install_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(port == 0);
    guard_irq_installs++;
    guard_irq_mode = mode;
    guard_irq_callback = callback;
    return true;
}
static inline void prepare_system_probe_guard(void)
{
    prepare_system_command();
    hal.port.register_interrupt_handler = guard_install_irq;
    hal.control.interrupt_callback = control_interrupt_handler;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_RisingFalling | IRQ_Mode_Change,
        &guard_probe_input, guard_read_input));
    hal.driver_cap.probe = true;
    CHECK(system_command("$65=32") == Status_OK); // Probing options: input protection enabled.
    CHECK(settings.probe.enable_protection);
    CHECK(guard_irq_callback != NULL && guard_irq_mode == IRQ_Mode_Change);
}
static inline void check_idle_guard_state(bool triggered)
{
    CHECK(state_get() == STATE_IDLE && sys.probing_state == Probing_Off);
    CHECK(hal.probe.get_state().triggered == triggered);
    CHECK(!hal.probe.get_state().is_probing && hal.probe.get_caps(Probe_Default).guarded);
    CHECK(guard_irq_mode == IRQ_Mode_Change);
    CHECK(!(sys.rt_exec_state & (EXEC_STOP | EXEC_FEED_HOLD | EXEC_RESET)));
    CHECK(sys.alarm_pending == Alarm_None && sys.alarm == Alarm_None);
    CHECK(plan_get_current_block() == NULL);
}
