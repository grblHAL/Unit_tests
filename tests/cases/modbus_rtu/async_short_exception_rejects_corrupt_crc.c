#include "support/rtu_short_exception_host.h"

int main(void)
{
    start_short_exception_request();
    uint8_t frame[5];
    make_short_exception(frame);
    frame[4] ^= 1;
    append_short_reply(frame, sizeof(frame));
    finish_short_exception(ModBus_CRCError);
    return EXIT_SUCCESS;
}
