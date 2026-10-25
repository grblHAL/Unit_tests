#include "pca_host.h"
int main(void)
{
#ifdef FAIL_START
    bus_ok = false;
#else
    device_present = false;
#endif
    start_expander();
    CHECK(starts == 1 && registrations == 0 && writes == 0 && enumerations == 0);
#ifdef FAIL_START
    CHECK(probes == 0);
#else
    CHECK(probes == 1);
#endif
    return 0;
}
