#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    uint_fast8_t i = 1; float value = 0;
    CHECK(read_float("X-12.5Y3", &i, &value)); NEAR(value, -12.5f); CHECK(i == 6);
    i = 0; CHECK(read_float("+.25", &i, &value)); NEAR(value, .25f); CHECK(i == 4);
    i = 0; CHECK(read_float("0", &i, &value)); NEAR(value, 0); CHECK(i == 1);
    return EXIT_SUCCESS;
}
