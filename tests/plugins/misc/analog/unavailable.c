#include "analog_host.h"
int main(void)
{
    prepare_analog();
#ifdef FAIL_START
    start_ok = false;
#else
    probe_ok = false;
#endif
    initialize_analog();
    CHECK(starts == 1 && registrations == 0 && reads == 0 && sends == 0);
#ifdef FAIL_START
    CHECK(probes == 0);
#else
    CHECK(probes == 1);
#endif
    return 0;
}
