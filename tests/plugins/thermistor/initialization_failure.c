#include "therm_host.h"
int main(void)
{
    therm_prepare();
    available_ports = 0;
    thermistor_init();
    CHECK(!registered_settings && !registered_commands && warnings == 1);
    available_ports = 2;
    alloc_ok = false;
    thermistor_init();
    CHECK(!registered_settings && !registered_commands && warnings == 2);
    return 0;
}
