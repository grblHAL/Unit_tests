#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    uint_fast8_t i = 1; float value = 0;
    CHECK(read_float("X-12.5Y3", &i, &value)); NEAR(value, -12.5f); CHECK(i == 6);
    i = 0; CHECK(read_float("+.25", &i, &value)); NEAR(value, .25f); CHECK(i == 4);
    i = 0; CHECK(read_float("0", &i, &value)); NEAR(value, 0); CHECK(i == 1);
    i = 0;
    CHECK(read_float("123456789012X", &i, &value));
    CHECK(fabsf(value / 123456789012.0f - 1.0f) < 0.000001f);
    CHECK(i == 12);
    i = 0;
    CHECK(read_float("1.234567890123Y", &i, &value));
    NEAR(value, 1.23456789f);
    CHECK(i == 14);
    return EXIT_SUCCESS;
}
