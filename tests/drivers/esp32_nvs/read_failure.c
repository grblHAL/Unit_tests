#include "esp_host.h"
int main(void)
{
    esp_prepare();
    CHECK(nvsInit());
    esp_read_ok = false;
    uint8_t data[1024];
    memset(data, 0x3C, sizeof(data));
    CHECK(!nvsRead(data));
    CHECK(!nvsWrite(data) && esp_reads == 1 && !esp_erases && esp_handler == esp_original_handler);
    for (unsigned i = 0; i < sizeof(data); i++)
        CHECK(data[i] == 0x3C);
    return 0;
}
