#include "support/named_parameter_host.h"
int main(void)
{
    engine_parser_prepare();
    NEAR(read_named_parameter("_vmajor"), 1.1f);
    NEAR(read_named_parameter("_vminor"), (float)(GRBL_BUILD - 20000000));
    return EXIT_SUCCESS;
}
