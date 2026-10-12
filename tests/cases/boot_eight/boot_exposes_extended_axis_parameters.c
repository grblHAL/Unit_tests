#include "support/boot_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[U_AXIS] = 400;
    CHECK(grbl_enter() == 0);
    char name[] = "_abs_u";
    float value;
    CHECK(ngc_named_param_get(name, &value));
    NEAR(value, 5);
    return EXIT_SUCCESS;
}
