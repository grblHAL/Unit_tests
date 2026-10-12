#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    for(unsigned round = 0; round < 4; round++) {
        for(unsigned i = 1; i < OVERRIDE_BUFSIZE; i++) enqueue_coolant_override((uint8_t)(i + round));
        for(unsigned i = 1; i < OVERRIDE_BUFSIZE; i++) CHECK(get_coolant_override() == i + round);
        CHECK(get_coolant_override() == 0);
    }
    return EXIT_SUCCESS;
}
