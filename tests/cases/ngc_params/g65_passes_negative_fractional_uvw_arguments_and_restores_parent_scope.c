#include "support/macro_uvw_argument_host.h"
int main(void)
{
    check_macro_uvw_arguments("G65P100U-2.5V-3.5W-4.5", -2.5f, -3.5f, -4.5f, false);
    return EXIT_SUCCESS;
}
