#include "nuts_bolts.h"
#include "check.h"
int main(void)
{
    CHECK(bit_count(0) == 0);
    CHECK(bit_count(UINT32_MAX) == 32);
    CHECK(bit_count(0x80000001) == 2);
    return EXIT_SUCCESS;
}
