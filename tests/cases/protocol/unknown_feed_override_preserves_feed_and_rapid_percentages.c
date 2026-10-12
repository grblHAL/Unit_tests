#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    unsigned feed = sys.override.feed_rate, rapid = sys.override.rapid_rate;
    enqueue_feed_override(0xEE); CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == feed); CHECK(sys.override.rapid_rate == rapid);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
