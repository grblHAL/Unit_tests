#include "flex_host.h"
int main(void)
{
    flex_prepare();
    claim_ok = false;
    flexgpio_init();
    flex_run();
    CHECK(bank.ports && warnings == 1);
    return 0;
}
