#include "mpg_host.h"
int main(void)
{
    mpg_start();
    CHECK(proxy.set_baud_rate(57600) && baud == 57600);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "baud=57600"));
    baud_ok = false;
    CHECK(!proxy.set_baud_rate(9600) && baud == 57600);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "baud=57600"));
    return 0;
}
