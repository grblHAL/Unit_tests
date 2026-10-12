#include <time.h>
#include "nuts_bolts.h"
#include "check.h"
int main(void)
{
    uint_fast8_t i = 0; uint32_t value = 0;
    read_uint("42.000", &i, &value);
    CHECK(value == 42);
    return EXIT_SUCCESS;
}
