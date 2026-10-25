#include "clone_host.h"
int main(void)
{
#if TEST_REJECT == 4
    clone_storage = false;
#endif
    clone_prepare();
    CHECK(!clone_settings && !clone_warnings && !spindle_get_hal(1, SpindleHAL_Raw));
    CHECK(!clone_calls);
    return 0;
}
