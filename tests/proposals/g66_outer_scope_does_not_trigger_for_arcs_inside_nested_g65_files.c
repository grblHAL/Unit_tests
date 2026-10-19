#include "support/scoped_modal_macro_protocol_host.h"
int main(void)
{
    run_scoped_modal_macro_program("G66P100X12\nG65P10L1A5\nG3X3Y2J1F100\nG67\n", "G0X1Y0\nG65P20L1A7\n", "G3X2Y1J1F100\n", 2);
    return EXIT_SUCCESS;
}
