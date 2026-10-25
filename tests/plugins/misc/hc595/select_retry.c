#include "spi_host.h"
int main(void)
{
    start_hc595();
    select_ok = false;
    bank.digital_out(0, true);
    CHECK(selections == 1 && transfers == 0 && deselections == 0);
    select_ok = true;
    bank.digital_out(0, true);
    CHECK(selections == 2 && transfers == 1 && deselections == 1 && shifted == 1);
    bank.digital_out(0, true);
    CHECK(selections == 2 && transfers == 1);
    bank.digital_out(0, false);
    CHECK(selections == 3 && transfers == 2 && deselections == 2 && shifted == 0);
    return 0;
}
