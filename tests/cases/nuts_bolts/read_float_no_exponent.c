#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    uint_fast8_t i = 0; float value;
    CHECK(read_float("1.5E3", &i, &value)); NEAR(value, 1.5f); CHECK(i == 3);
    i = 0; CHECK(read_float("1.2.3", &i, &value)); NEAR(value, 1.2f); CHECK(i == 3);
    return EXIT_SUCCESS;
}
