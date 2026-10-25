#include "flex_host.h"
int main(void)
{
    flex_prepare();
    probe_ok = false;
    flexgpio_init();
    flex_run();
    CHECK(!bank.ports && sends == 0);
    return 0;
}
