#include "support/spindle_linearization_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_linearization();
    compute_spindle_pwm();
    CHECK(pwm_data.compute_value(&pwm_data, 4000, false) == 400);
    return EXIT_SUCCESS;
}
