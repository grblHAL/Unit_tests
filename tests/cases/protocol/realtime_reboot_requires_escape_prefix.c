#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned reboot_calls;
static void reboot(void) { reboot_calls++; }
int main(void)
{
    engine_prepare();
    hal.reboot = reboot;
    protocol_enqueue_realtime_command(CMD_REBOOT);
    CHECK(reboot_calls == 0);
    CHECK(protocol_enqueue_realtime_command(ASCII_ESC));
    protocol_enqueue_realtime_command(CMD_REBOOT);
    CHECK(reboot_calls == 1);
    return EXIT_SUCCESS;
}
