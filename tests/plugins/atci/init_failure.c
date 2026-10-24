#include "atci_host.h"
int main(void)
{
    atci_prepare();
    alloc_ok = false;
    atci_init();
    CHECK(!registered_settings && atci_check(20, 20));
    return 0;
}
