#include "nuts_bolts.h"
#include "check.h"
int main(void)
{
    const char *inputs[] = {"1000000006", "2000000009", "4294967289"};
    const uint32_t expected[] = {1000000006u, 2000000009u, 4294967289u};
    for(unsigned i = 0; i < 3; i++) {
        uint_fast8_t consumed = 0;
        uint32_t actual = 0;
        CHECK(read_uint(inputs[i], &consumed, &actual) == Status_OK);
        CHECK(actual == expected[i] && consumed == 10);
    }
    return EXIT_SUCCESS;
}
