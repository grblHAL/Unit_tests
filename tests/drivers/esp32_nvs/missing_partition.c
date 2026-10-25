#include "esp_host.h"
int main(void)
{
    esp_prepare();
    esp_found = false;
    CHECK(!nvsInit());
    uint8_t data[1024] = {0};
    CHECK(!nvsRead(data) && !nvsWrite(data));
    CHECK(!esp_reads && !esp_writes && !esp_erases && esp_handler == esp_original_handler &&
          esp_handler_changes == 2);
    return 0;
}
