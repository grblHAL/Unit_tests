#include "support/lathe_modal_report_host.h"

int main(void)
{
    check_roughing_mode_report("G71.2X10Z20Q7F100", "[GC:G71.2 ");
    return EXIT_SUCCESS;
}
