#include "esp_host.h"
int main(void)
{
    esp_prepare();
    CHECK(nvsInit());
    uint8_t data[1024];
    esp_read_ok = false;
    CHECK(!nvsRead(data));
    esp_read_ok = true;
    CHECK(nvsInit() && nvsRead(data) && esp_reads == 2);
    return 0;
}
