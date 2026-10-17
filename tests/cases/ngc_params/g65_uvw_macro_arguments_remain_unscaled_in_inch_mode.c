#include "support/macro_uvw_argument_host.h"
int main(void)
{
    check_macro_uvw_arguments("G65P100U2.5V3.5W4.5", 2.5f, 3.5f, 4.5f, true);
    return EXIT_SUCCESS;
}
