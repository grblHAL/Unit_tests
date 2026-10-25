#include "at_host.h"
int main(void)
{
    at_prepare();
#if AT_NO_UART
    at_uart_available = false;
#else
    at_storage_available = false;
#endif
    void esp_at_init(void);
    esp_at_init();
    CHECK(!at_settings && at_pending() == 1);
    at_step(0);
    CHECK(at_warnings == 1 && !at_commands[0] && !at_pending());
    CHECK(strstr(at_output, "ESP-AT plugin failed to initialize!"));
    return 0;
}
