#include "vinput_host.h"
int main(void)
{
    vi_prepare(true);
    virtual_inputs_init();
    CHECK(warnings == 1 && registrations == 0);
    vi_start(true);
    CHECK(warnings == 1 && registrations == 1);
    return 0;
}
