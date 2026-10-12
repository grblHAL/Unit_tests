#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    CHECK(store_setting(Setting_LinearSpindlePiece1, "1000,1,0") == Status_OK);
    CHECK(store_setting(Setting_LinearSpindlePiece2, "5000,0.5,-2500") == Status_OK);
    CHECK(spindle_precompute_pwm_values(&pwm_spindle, &pwm_data, &settings.pwm_spindle, 1000000));
    CHECK(pwm_data.n_pieces == 2 && pwm_spindle.cap.pwm_linearization);
    CHECK(pwm_data.compute_value(&pwm_data, 5000, false) == 500);
    CHECK(pwm_data.compute_value(&pwm_data, 4000, false) == 400);
    CHECK(pwm_data.compute_value(&pwm_data, 7000, false) == 600);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
