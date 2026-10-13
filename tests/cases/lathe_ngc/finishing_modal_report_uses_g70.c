#include "support/lathe_modal_report_host.h"

int main(void)
{
    check_roughing_mode_report("G70X10Z20Q7F100", "[GC:G70 ");
    return EXIT_SUCCESS;
}
