#include "support/spindle_linearization_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_linearization();
    pwm_settings.pwm_piece[1].start = 0;
    compute_spindle_pwm();
    CHECK(pwm_data.n_pieces == 1);
    CHECK(pwm_data.compute_value(&pwm_data, 7000, false) == 700);
    return EXIT_SUCCESS;
}
