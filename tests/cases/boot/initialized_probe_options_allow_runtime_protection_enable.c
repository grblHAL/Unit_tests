#include "support/boot_probe_protection_host.h"
#include "probe.h"
static bool initialized_probe_input, guard_irq_requested;
static bool read_initialized_probe(void *input) { CHECK(input == &initialized_probe_input); return initialized_probe_input; }
static bool initialized_probe_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(port == 0);
    (void)callback;
    guard_irq_requested |= mode == IRQ_Mode_Change;
    return true;
}
static void setup_initialized_probe(settings_t *current)
{
    CHECK(current == &settings);
    hal.port.register_interrupt_handler = initialized_probe_irq;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_RisingFalling | IRQ_Mode_Change,
        &initialized_probe_input, read_initialized_probe));
    hal.driver_cap.probe = true;
}
int main(void)
{
    boot_program = "$65=32\n$65\n";
    boot_during_init = install_probe_protection;
    boot_during_setup = setup_initialized_probe;
    CHECK(grbl_enter() == 0);
    CHECK(hal.probe.get_caps(Probe_Default).watchable);
    CHECK(settings.probe.enable_protection && guard_irq_requested);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "$65=32" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
