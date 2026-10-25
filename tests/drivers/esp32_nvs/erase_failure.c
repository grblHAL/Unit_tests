#include "esp_host.h"
int main(void)
{
    esp_prepare();
    CHECK(nvsInit());
    esp_erase_ok = false;
    uint8_t data[1024] = {0};
    CHECK(!nvsWrite(data));
    CHECK(esp_erases == 1 && !esp_writes && esp_handler == esp_original_handler &&
          esp_handler_changes == 2);
    return 0;
}
