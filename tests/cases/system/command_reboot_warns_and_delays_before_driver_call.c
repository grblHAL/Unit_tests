#include "support/system_command_host.h"
#include "check.h"
static unsigned reboot_calls, delay_calls;
static void delay(uint32_t ms, delay_callback_ptr callback) { CHECK(ms == 100); CHECK(callback == NULL); CHECK(reboot_calls == 0); CHECK(strstr(engine_output, "Rebooting controller") != NULL); delay_calls++; }
static void reboot(void) { CHECK(delay_calls == 1); reboot_calls++; }
int main(void)
{
    prepare_system_command();
    hal.reboot = reboot;
    hal.delay_ms = delay;
    CHECK(system_command("$REBOOT") == Status_OK);
    CHECK(reboot_calls == 1);
    CHECK(delay_calls == 1);
    return EXIT_SUCCESS;
}
