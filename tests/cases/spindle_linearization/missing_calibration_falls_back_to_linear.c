#include "support/spindle_linearization_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_linearization();
    for(unsigned i = 0; i < SPINDLE_NPWM_PIECES; i++)
        pwm_settings.pwm_piece[i] = (pwm_piece_t){.rpm = NAN};
    compute_spindle_pwm();
    CHECK(pwm_data.n_pieces == 0 && !pwm_spindle.cap.pwm_linearization);
    CHECK(pwm_data.compute_value(&pwm_data, 7000, false) == 700);
    return EXIT_SUCCESS;
}
