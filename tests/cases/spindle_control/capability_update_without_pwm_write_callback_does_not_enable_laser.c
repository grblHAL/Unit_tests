#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(true);
    configured->update_pwm = NULL;
    spindle_update_caps(configured,&pwm_data);
    CHECK(!spindle_get(0)->cap.laser && !configured->cap.laser);
    return EXIT_SUCCESS;
}
