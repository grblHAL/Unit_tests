#include "esp_host.h"
int main(void)
{
    esp_prepare();
    CHECK(nvsInit());
    uint8_t data[1024];
    memset(data, 0xA5, sizeof(data));
    esp_write_ok = false;
    CHECK(!nvsWrite(data));
    esp_write_ok = true;
    CHECK(nvsWrite(data) && !memcmp(esp_memory, data, sizeof(data)));
    CHECK(esp_handler == esp_original_handler && esp_erases == 2 && esp_writes == 2 &&
          esp_handler_changes == 4);
    return 0;
}
