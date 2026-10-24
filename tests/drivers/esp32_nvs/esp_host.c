#include "esp_host.h"
grbl_hal_t hal;
uint8_t esp_memory[4096];
unsigned esp_reads, esp_writes, esp_erases, esp_handler_changes, esp_filter_checks;
bool esp_found = true, esp_read_ok = true, esp_write_ok = true, esp_erase_ok = true;
enqueue_realtime_command_ptr esp_handler;
static const esp_partition_t partition = {.size = 4096};
bool esp_original_handler(uint8_t c)
{
    (void)c;
    CHECK(false);
    return false;
}
static enqueue_realtime_command_ptr set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr old = esp_handler;
    esp_handler = handler;
    esp_handler_changes++;
    return old;
}
void esp_prepare(void)
{
    memset(esp_memory, 255, sizeof(esp_memory));
    hal.nvs.size = 1024;
    hal.stream.set_enqueue_rt_handler = set_handler;
    esp_handler = esp_original_handler;
}
const esp_partition_t *esp_partition_find_first(int type, int subtype, const char *label)
{
    CHECK(type == ESP_PARTITION_TYPE_DATA && subtype == ESP_PARTITION_SUBTYPE_ANY &&
          !strcmp(label, "grbl"));
    return esp_found ? &partition : NULL;
}
esp_err_t esp_partition_read(const esp_partition_t *p, size_t offset, void *data, size_t size)
{
    CHECK(p == &partition && !offset && size == hal.nvs.size);
    esp_reads++;
    if (esp_read_ok)
        memcpy(data, esp_memory, size);
    return esp_read_ok ? ESP_OK : ESP_FAIL;
}
esp_err_t esp_partition_erase_range(const esp_partition_t *p, size_t offset, size_t size)
{
    CHECK(p == &partition && !offset && size == SPI_FLASH_SEC_SIZE);
    CHECK(esp_handler && esp_handler != esp_original_handler);
    for (unsigned c = 0; c <= 255; c++)
    {
        CHECK(esp_handler(c) == ((c < 32 && c != 13 && c != 10) || c == '?' || c >= 127));
        esp_filter_checks++;
    }
    esp_erases++;
    if (esp_erase_ok)
        memset(esp_memory, 255, size);
    return esp_erase_ok ? ESP_OK : ESP_FAIL;
}
esp_err_t esp_partition_write(const esp_partition_t *p, size_t offset, const void *data,
                              size_t size)
{
    CHECK(p == &partition && !offset && size == hal.nvs.size &&
          esp_handler != esp_original_handler);
    esp_writes++;
    if (esp_write_ok)
        memcpy(esp_memory, data, size);
    return esp_write_ok ? ESP_OK : ESP_FAIL;
}
