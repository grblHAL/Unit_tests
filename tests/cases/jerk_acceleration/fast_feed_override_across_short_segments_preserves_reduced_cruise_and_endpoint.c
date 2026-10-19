#include "support/fast_jerk_motion_host.h"
int main(void)
{
    fast_configuration_hook = configure_fast_jerk_limits;
    /* Allow the longer jerk-limited deceleration to finish before sampling. */
    override_sample_start_step = 22400;
    override_sample_end_step = 23200;
    run_fast_override(false);
    return EXIT_SUCCESS;
}
