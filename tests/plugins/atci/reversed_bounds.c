#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    atci_bounds(50, 50, 10, 10);
    CHECK(!atci_check(20, 20));
    CHECK(atci_check(-10, -10));
    output[0] = 0;
    grbl.on_report_ngc_parameters();
    CHECK(strstr(output, "[ATCI:50.00,10.00,50.00,10.00]"));
    return 0;
}
