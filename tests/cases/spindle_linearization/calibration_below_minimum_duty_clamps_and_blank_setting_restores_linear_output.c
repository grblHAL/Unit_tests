#include "support/linearization_settings_host.h"
int main(void)
{
    prepare_linearization_settings();
    CHECK(store_setting(Setting_LinearSpindlePiece1, "1000,0.01,0") == Status_OK);
    CHECK(spindle_precompute_pwm_values(&pwm_spindle, &pwm_data, &settings.pwm_spindle, 1000000));
    CHECK(pwm_data.n_pieces == 1 && pwm_spindle.cap.pwm_linearization);
    CHECK(pwm_data.compute_value(&pwm_data, 1500, false) == pwm_data.min_value);
    CHECK(pwm_data.compute_value(&pwm_data, 1500, true) == pwm_data.min_value);
    CHECK(pwm_data.compute_value(&pwm_data, 0, false) == pwm_data.off_value);
    CHECK(store_setting(Setting_LinearSpindlePiece1, "") == Status_OK);
    CHECK(spindle_precompute_pwm_values(&pwm_spindle, &pwm_data, &settings.pwm_spindle, 1000000));
    CHECK(pwm_data.n_pieces == 0 && !pwm_spindle.cap.pwm_linearization);
    CHECK(pwm_data.compute_value(&pwm_data, 1500, false) == 150);
    CHECK(pwm_data.compute_value(&pwm_data, 0, false) == pwm_data.off_value);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
