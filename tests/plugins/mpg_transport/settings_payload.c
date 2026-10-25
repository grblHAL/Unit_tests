#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    *(uint8_t *)registered_settings->settings[2].value = 8;
    registered_settings->on_changed(&settings, (settings_changed_flags_t){0});
    const uint8_t data[] = "G1X12Y34F100\nG0X0\n";
    const size_t length = sizeof(data) - 1;
    proxy.write_n(data, length);
    CHECK(packets == 1 && sent[0].data[3] == 8);
    size_t offset = 0;
    for (unsigned i = 0; offset < length; i++)
    {
        CHECK(i < packets);
        size_t size = sent[i].data[3];
        CHECK(size > 0 && size <= 8 && offset + size <= length &&
              memcmp(sent[i].data + 4, data + offset, size) == 0);
        offset += size;
        mpg_ack(i);
        CHECK(proxy.get_tx_buffer_count() == length - offset);
    }
    CHECK(packets == 3 && warnings == 0);
    return 0;
}
