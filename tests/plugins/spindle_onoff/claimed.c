#include "onoff_host.h"
int main(void)
{
    on_prepare(2);
    on_settings->restore();
    CHECK(on_set(Setting_Spindle_OnPort, 0) == Status_OK);
    on_settings->save();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Other plugin"));
    on_load();
    CHECK(on_warnings == 1 && !spindle_get(0) && !on_writes);
    return 0;
}
