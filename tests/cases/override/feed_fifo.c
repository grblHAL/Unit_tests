#include <stdint.h>
#include "override.h"
#include "check.h"
int main(void)
{
    flush_override_buffers();
    CHECK(get_feed_override() == 0);
    enqueue_feed_override(10); enqueue_feed_override(20);
    CHECK(get_feed_override() == 10); CHECK(get_feed_override() == 20);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
