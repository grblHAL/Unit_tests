#include "esp_host.h"
int main(void)
{
    esp_prepare();
    CHECK(nvsInit());
    uint8_t data[1024], out[1024];
    for (unsigned i = 0; i < sizeof(data); i++)
        data[i] = i * 13;
    CHECK(nvsWrite(data) && nvsRead(out) && !memcmp(data, out, sizeof(data)));
    CHECK(esp_reads == 1 && esp_writes == 1 && esp_erases == 1 && esp_handler_changes == 2 &&
          esp_filter_checks == 256 && esp_handler == esp_original_handler);
    return 0;
}
