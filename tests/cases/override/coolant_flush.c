#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    enqueue_coolant_override(10); enqueue_coolant_override(20);
    flush_override_buffers(); CHECK(get_coolant_override() == 0);
    enqueue_coolant_override(30); CHECK(get_coolant_override() == 30);
    return EXIT_SUCCESS;
}
