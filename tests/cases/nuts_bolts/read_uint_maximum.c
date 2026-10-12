#include <time.h>
#include "nuts_bolts.h"
#include "check.h"
int main(void)
{
    uint_fast8_t i = 0; uint32_t value = 0;
    read_uint("4294967295", &i, &value);
    CHECK(value == UINT32_MAX);
    return EXIT_SUCCESS;
}
