#include "support/scoped_modal_macro_protocol_host.h"
int main(void)
{
    run_scoped_modal_macro_program("G66P100X12\nG65P10L1A5\nG1X3F100\nG67\n", "G1X1F100\nG65P20L1A7\n", "G1X2F100\n", 0);
    return EXIT_SUCCESS;
}
