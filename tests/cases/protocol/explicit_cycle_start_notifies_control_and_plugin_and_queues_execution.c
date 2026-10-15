#include "support/realtime_start_callback_host.h"
int main(void)
{
    verify_realtime_start_callbacks(CMD_CYCLE_START);
    return EXIT_SUCCESS;
}
