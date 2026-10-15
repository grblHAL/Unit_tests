#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    CHECK(N_AXIS == 6);
    const parameter_words_t words[] = {{.x = true}, {.y = true}, {.z = true}, {.u = true}, {.v = true}, {.w = true}};
    const uint8_t expected[] = {1, 2, 4, 8, 16, 32};
    for(unsigned i = 0; i < sizeof(expected) / sizeof(expected[0]); i++)
        CHECK(gc_paramwords_to_axes(words[i]).mask == expected[i]);
    return EXIT_SUCCESS;
}
