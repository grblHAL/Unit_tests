#include "bltouch_host.h"
int main(void)
{
    readback_enabled = false;
    load_bltouch();
    CHECK(angle == 90 && outputs == 1);
    unsigned before = delays;
    command_bltouch(Probe_Stow);
    CHECK(outputs == 1 && delays == before);
    command_bltouch(Probe_Deploy);
    CHECK(angle == 10 && outputs == 2);
    before = delays;
    command_bltouch(Probe_Deploy);
    CHECK(outputs == 2 && delays == before);
    command_bltouch(Probe_Stow);
    CHECK(angle == 90 && outputs == 3);
    return 0;
}
