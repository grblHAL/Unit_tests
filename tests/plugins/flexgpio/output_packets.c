#include "flex_host.h"
int main(void)
{
    flex_start();
    bank.digital_out(0, true);
    CHECK(last_size == 4 && last_packet[2] == 0x80);
    bank.digital_out(1, true);
    CHECK(last_packet[2] == 0xC0);
    unsigned before = sends;
    bank.digital_out(1, true);
    CHECK(sends == before);
    bank.digital_out(0, false);
    CHECK(last_packet[2] == 0x40);
    bank.digital_out(255, true);
    CHECK(sends == before + 1);
    return 0;
}
