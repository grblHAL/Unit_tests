#include "mpg_host.h"
int main(void)
{
    mpg_core_start();
    const uint8_t commands[] = "$I\n$G\n$$\n";
    mpg_receive(1, MpgFrame_Dat, commands, sizeof(commands) - 1);
    CHECK(command_calls == 0 && proxy.get_rx_buffer_count() == 0);
    mpg_core_run();
    CHECK(command_calls == 3);
    fprintf(stderr, "Command order: [%s] [%s] [%s]\n", command_history[0], command_history[1],
            command_history[2]);
    CHECK(strcmp(command_history[0], "$I") == 0 && strcmp(command_history[1], "$G") == 0 &&
          strcmp(command_history[2], "$$") == 0);
    return 0;
}
