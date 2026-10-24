#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t data = 'G';
    mpg_receive(1, MpgFrame_Dat, &data, 1);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "rxdata=1"));
    CHECK(mpg_command(" reset ") == Status_OK);
    mpg_receive(1, MpgFrame_Dat, &data, 1);
    CHECK(proxy.get_rx_buffer_count() == 1);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "rxdata=0,rxdup=1"));
    CHECK(mpg_command("bad") == Status_InvalidStatement);
    return 0;
}
