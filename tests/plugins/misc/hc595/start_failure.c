#include "spi_host.h"
int main(void)
{
    start_ok = false;
    start_hc595();
    CHECK(starts == 1 && registrations == 0 && selections == 0 && transfers == 0);
    return 0;
}
