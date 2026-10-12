#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned reboot_calls;
static void reboot(void) { reboot_calls++; }
int main(void)
{
    engine_prepare();
    hal.reboot = reboot;
    CHECK(protocol_enqueue_realtime_command(ASCII_ESC));
    CHECK(!protocol_enqueue_realtime_command('A'));
    protocol_enqueue_realtime_command(CMD_REBOOT);
    CHECK(reboot_calls == 0);
    return EXIT_SUCCESS;
}
