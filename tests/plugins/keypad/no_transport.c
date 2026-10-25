#include "key_host.h"
int main(void)
{
    key_prepare();
    key_bus_ok = key_uart_ok = false;
#if KEYPAD_ENABLE == 1
    CHECK(!keypad_init());
#else
    (void)keypad_init();
#endif
    CHECK(!key_settings);
    return 0;
}
