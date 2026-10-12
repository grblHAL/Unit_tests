#include "support/boot_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    boot_program = "#100=7\n(PRINT,part=#100)\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "part=7.000") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
