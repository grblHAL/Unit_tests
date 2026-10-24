#include "support/boot_host.h"
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
static stream_write_ptr output_all;
static unsigned welcomes, recovered;
static void contact_after_warm_welcome(const char *text)
{
    output_all(text);
    if(strstr(text, "GrblHAL") && ++welcomes == 2) {
        CHECK(settings.probe.enable_protection);
        boot_control_signals.probe_triggered = true;
    }
}
static void install_guard_and_welcome(settings_t *current)
{
    setup_initialized_probe(current);
    output_all = hal.stream.write_all;
    hal.stream.write_all = contact_after_warm_welcome;
}
static void clear_after_rejected_probe_command(void)
{
    if(boot_reads == 12) {
        CHECK(sys.alarm == Alarm_ProbeProtect && state_get() == STATE_ALARM);
        CHECK(!gc_state.modal.distance_incremental);
        CHECK(strstr(engine_output, "error:9") != NULL);
        boot_control_signals.probe_triggered = false;
        recovered++;
        boot_before_read = NULL;
    }
}
int main(void)
{
    boot_during_setup = install_guard_and_welcome;
    boot_before_read = clear_after_rejected_probe_command;
    boot_program = "$65=32\n\x18" "G91\n$X\nG91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(welcomes == 2 && recovered == 1);
    CHECK(settings.probe.enable_protection && guard_irq_requested);
    CHECK(strstr(engine_output, "ALARM:13") != NULL);
    CHECK(gc_state.modal.distance_incremental && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G91") != NULL);
    return EXIT_SUCCESS;
}
