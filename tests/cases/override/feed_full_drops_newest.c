#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    for(unsigned i = 1; i < OVERRIDE_BUFSIZE; i++) enqueue_feed_override((uint8_t)i);
    enqueue_feed_override(200);
    for(unsigned i = 1; i < OVERRIDE_BUFSIZE; i++) CHECK(get_feed_override() == i);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
