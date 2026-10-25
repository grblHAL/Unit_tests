#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    uint_fast8_t i = 1; uint32_t value;
    CHECK(read_uint("X+123Y", &i, &value) == Status_OK); CHECK(value == 123); CHECK(i == 5);

    i = 0; CHECK(read_uint("4294967294", &i, &value) == Status_OK); CHECK(value == UINT32_MAX - 1); CHECK(i == 10);
    i = 0; value = 99;
    CHECK(read_uint("0", &i, &value) == Status_OK);
    CHECK(value == 0 && i == 1);
    i = 1; value = 99;
    CHECK(read_uint("X00012Y", &i, &value) == Status_OK);
    CHECK(value == 12 && i == 6);
    return EXIT_SUCCESS;
}
