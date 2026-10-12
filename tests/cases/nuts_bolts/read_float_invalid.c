#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    const char *invalid[] = {"", "+", "-", ".", "X", " 12"};
    for(unsigned n = 0; n < sizeof(invalid)/sizeof(invalid[0]); n++) {
    uint_fast8_t i = 0; float value = 123;
    CHECK(!read_float(invalid[n], &i, &value)); CHECK(i == 0); NEAR(value, 123);
    }
    return EXIT_SUCCESS;
}
