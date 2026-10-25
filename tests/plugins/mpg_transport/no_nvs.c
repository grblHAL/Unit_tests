#include "mpg_host.h"
int main(void)
{
    mpg_prepare();
    alloc_ok = false;
    mpg_init();
    CHECK(warnings == 1 && !registered_settings && claims == 0);
    unsigned before = chains;
    grbl.on_report_options(false);
    CHECK(chains == before + 2);
    return 0;
}
