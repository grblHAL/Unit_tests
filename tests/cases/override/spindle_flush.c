#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    enqueue_spindle_override(10); enqueue_spindle_override(20);
    flush_override_buffers(); CHECK(get_spindle_override() == 0);
    enqueue_spindle_override(30); CHECK(get_spindle_override() == 30);
    return EXIT_SUCCESS;
}
