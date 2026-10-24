#include "sam_host.h"
int main(void)
{
    sam_mux_dirty = true;
    sam_prepare();
    CHECK(!(PIOB->PIO_ABSR & ((1U << 20) | (1U << 21))) && (PIOB->PIO_ABSR & (1U << 6)));
    CHECK(!(PIOA->PIO_ABSR & ((1U << 12) | (1U << 13))) && (PIOA->PIO_ABSR & (1U << 5)));
    return 0;
}
