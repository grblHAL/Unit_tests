#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        CHECK(sam_stream[n]->write_char('G' + n));
        CHECK(sam_last_tx(n) == 'G' + n && !sam_stream[n]->get_tx_buffer_count());
    }
    return 0;
}
