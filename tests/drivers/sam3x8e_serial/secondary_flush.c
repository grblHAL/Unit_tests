#include "sam_host.h"
int main(void)
{
    sam_prepare();
    CHECK(sam_stream[1]->reset_write_buffer);
    sam_busy(1, true);
    sam_stream[1]->write("M3S500\n");
    sam_stream[1]->reset_write_buffer();
    sam_busy(1, false);
    CHECK(!sam_stream[1]->get_tx_buffer_count());
    return 0;
}
