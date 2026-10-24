#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    uint_fast8_t i = 0; uint32_t value = 99;
    CHECK(read_uint("-1", &i, &value) == Status_NegativeValue); CHECK(i == 0); CHECK(value == 99);
    CHECK(read_uint("1.5", &i, &value) == Status_GcodeCommandValueNotInteger); CHECK(i == 0); CHECK(value == 99);
    CHECK(read_uint("abc", &i, &value) == Status_BadNumberFormat); CHECK(i == 0); CHECK(value == 99);
    const char *overflow[] = {"4294967296", "4294967300"};
    for(unsigned n = 0; n < sizeof(overflow) / sizeof(overflow[0]); n++) {
        CHECK(read_uint(overflow[n], &i, &value) == Status_SettingValueOutOfRange);
        CHECK(i == 0 && value == 99);
    }
    return EXIT_SUCCESS;
}
