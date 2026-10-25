#include "seal_host.h"
int main(void)
{
    seal_prepare();
    alloc_ok = false;
    pneumaseal_init();
    CHECK(!registered_settings && warnings == 1 && claims == 0);
    return 0;
}
