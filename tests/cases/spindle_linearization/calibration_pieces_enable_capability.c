#include "support/spindle_linearization_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_linearization();
    compute_spindle_pwm();
    CHECK(pwm_data.n_pieces == 2 && pwm_spindle.cap.pwm_linearization);
    return EXIT_SUCCESS;
}
