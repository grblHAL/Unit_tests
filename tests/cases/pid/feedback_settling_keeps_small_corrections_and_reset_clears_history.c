#include "pid.h"
#include "check.h"
int main(void)
{
    pidf_t pid = {0};
    pid_values_t config = {.p_gain = 1, .i_gain = 0.5f, .d_gain = 0.25f,
        .i_max_error = 4, .d_max_error = 2, .max_error = 10};
    pidf_init(&pid, &config);
    // Feedback reaches the setpoint, overshoots slightly, then settles.
    const float actual[] = {999, 999.5f, 1000, 1000.5f, 1000};
    const float expected[] = {1.75f, 1.125f, 0.625f, -0.125f, 0.625f};
    for(unsigned sample = 0; sample < sizeof(actual) / sizeof(actual[0]); sample++) {
        NEAR(pidf(&pid, 1000, actual[sample], 1), expected[sample]);
        NEAR(pid.error, expected[sample]);
    }
    pidf_reset(&pid);
    CHECK(!pidf_config_changed(&pid, &config));
    NEAR(pidf(&pid, 1000, 1000, 1), 0);
    NEAR(pid.i_error, 0);
    NEAR(pid.d_error, 0);
    return EXIT_SUCCESS;
}
