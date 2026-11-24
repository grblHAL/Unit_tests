#include "clone_host.h"
int main(void)
{
    clone_available = false;
    clone_prepare();
    CHECK(clone_settings && spindle_select(0));
    spindle_ptrs_t *primary = spindle_get(0);
    CHECK(primary && primary->cap.direction && !primary->cap.clone);
    CHECK(!spindle_select(1));
    CHECK(spindle_get(0) == primary && !clone_warnings);
    return 0;
}
