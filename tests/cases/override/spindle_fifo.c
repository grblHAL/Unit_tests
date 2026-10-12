#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    CHECK(get_spindle_override() == 0);
    enqueue_spindle_override(10); enqueue_spindle_override(20);
    CHECK(get_spindle_override() == 10); CHECK(get_spindle_override() == 20);
    CHECK(get_spindle_override() == 0);
    return EXIT_SUCCESS;
}
