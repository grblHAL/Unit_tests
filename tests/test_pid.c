#include "pid.h"
#include "check.h"

int main(void)
{
    pidf_t pid = {0};
    pid_values_t cfg = {0};
    cfg.p_gain = 2;
    pidf_init(&pid, &cfg);
    CHECK(!pidf_config_changed(&pid, &cfg));
    cfg.p_gain = 3;
    CHECK(pidf_config_changed(&pid, &cfg));
    NEAR(pidf(&pid, 10, 7, 1), 6);
    NEAR(pidf(&pid, 7, 10, 1), -6);
    NEAR(pidf(&pid, 7, 7, 1), 0);
    cfg = (pid_values_t){0};
    cfg.i_gain = 2;
    cfg.i_max_error = 3;
    pidf_init(&pid, &cfg);
    NEAR(pidf(&pid, 2, 0, 1), 4);
    NEAR(pidf(&pid, 2, 0, 1), 6);
    NEAR(pidf(&pid, 0, 20, 1), -6);
    cfg.i_max_error = 0;
    pidf_init(&pid, &cfg);
    NEAR(pidf(&pid, 4, 0, 2), 4);
    NEAR(pidf(&pid, 4, 0, 1), 20);
    cfg = (pid_values_t){0};
    cfg.d_gain = 2;
    pidf_init(&pid, &cfg);
    NEAR(pidf(&pid, 3, 0, 1), 6);
    NEAR(pidf(&pid, 3, 0, 1), 0);
    NEAR(pidf(&pid, 1, 0, 2), -8);
    cfg.d_max_error = 1;
    pidf_init(&pid, &cfg);
    NEAR(pidf(&pid, 10, 0, 1), 2);
    NEAR(pidf(&pid, -10, 0, 1), -2);
    cfg = (pid_values_t){0};
    cfg.p_gain = 10;
    cfg.max_error = 5;
    pidf_init(&pid, &cfg);
    NEAR(pidf(&pid, 2, 0, 1), 5);
    NEAR(pidf(&pid, 0, 2, 1), -5);
    NEAR(pid.error, -5);
    pidf_reset(&pid);
    NEAR(pid.error, 0);
    NEAR(pid.i_error, 0);
    NEAR(pid.d_error, 0);
    NEAR(pid.sample_rate_prev, 1);
    NEAR(pid.cfg.p_gain, 10);
    puts("PID checks passed");
    return EXIT_SUCCESS;
}
