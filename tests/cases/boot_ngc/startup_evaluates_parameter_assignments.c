#include "support/boot_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    boot_program = "#100=7\n#101=[#100*3]\n";
    CHECK(grbl_enter() == 0);
    float value;
    CHECK(ngc_param_get(101, &value));
    NEAR(value, 21);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
