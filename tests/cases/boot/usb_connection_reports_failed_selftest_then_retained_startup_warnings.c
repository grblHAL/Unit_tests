#include "support/boot_host.h"
#include "task.h"
#include "report.h"
static unsigned fault_turns, forbidden_calls;
static uint32_t connected_at;
static void forbidden_startup_task(void *data) { (void)data; forbidden_calls++; }
static void configure_failed_usb_driver(void)
{
    hal.stream.state.is_usb = true;
    hal.stream.state.linestate_event = true;
    CHECK(task_run_on_startup(report_warning, "First fixture warning"));
    CHECK(task_run_on_startup(forbidden_startup_task, NULL));
    CHECK(task_run_on_startup(report_warning, "Second fixture warning"));
}
static void observe_failed_usb_driver(sys_state_t state)
{
    CHECK(++fault_turns < 100);
    CHECK(state == STATE_ALARM && sys.alarm == Alarm_SelftestFailed);
    CHECK(!sys.driver_started && forbidden_calls == 0);
    engine_ticks += 10;
    CHECK(hal.stream.on_linestate_changed != NULL);
    if(fault_turns == 1) {
        io_stream_properties_t usb = {.flags = {.is_usb = true}};
        io_stream_properties_t uart = {0};
        hal.stream.on_linestate_changed(&usb, (serial_linestate_t){0});
        hal.stream.on_linestate_changed(&uart, (serial_linestate_t){.dtr = true});
    }
    if(fault_turns <= 7) {
        CHECK(strstr(engine_output, "power on self-test (POS) failed!") == NULL);
        CHECK(strstr(engine_output, "fixture warning") == NULL);
    }
    if(fault_turns == 7) {
        io_stream_properties_t usb = {.flags = {.is_usb = true}};
        connected_at = engine_ticks;
        hal.stream.on_linestate_changed(&usb, (serial_linestate_t){.dtr = true});
    }
    const char *failure = strstr(engine_output, "grblHAL: power on self-test (POS) failed!");
    if(failure) {
        CHECK(engine_ticks >= connected_at + 50);
        const char *first = strstr(failure, "First fixture warning");
        const char *second = strstr(failure, "Second fixture warning");
        CHECK(first && second && first < second);
        CHECK(boot_setup_calls == 1 && boot_release_calls == 0);
        /* Failed startup intentionally stays in its fault loop. Finish only
           after observing the public connection event and delayed diagnostics. */
        exit(EXIT_SUCCESS);
    }
}
int main(void)
{
    boot_setup_success = false;
    boot_observe_fault_loop = true;
    boot_program = "";
    boot_during_init = configure_failed_usb_driver;
    boot_on_realtime = observe_failed_usb_driver;
    (void)grbl_enter();
    CHECK(false);
    return EXIT_FAILURE;
}
