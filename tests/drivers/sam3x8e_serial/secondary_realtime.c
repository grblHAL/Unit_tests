#include "sam_host.h"
static unsigned primary_count, secondary_count;
static bool primary(uint8_t c)
{
    CHECK(c == 0x85);
    primary_count++;
    return true;
}
static bool secondary(uint8_t c)
{
    CHECK(c == 0x85);
    secondary_count++;
    return true;
}
int main(void)
{
    sam_prepare();
    sam_stream[0]->set_enqueue_rt_handler(primary);
    sam_stream[1]->set_enqueue_rt_handler(secondary);
    bool ok = sam_stream[1]->enqueue_rt_command(0x85);
    CHECK(ok && secondary_count == 1 && !primary_count);
    return 0;
}
