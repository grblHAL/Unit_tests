#include "vfd_host.h"
int main(void)
{
    vfd_prepare(false);
    CHECK(!vfd_settings && spindle_get_name(0) == NULL && vfd_requests == 0);
    return 0;
}
