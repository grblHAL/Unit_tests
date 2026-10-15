#include "support/engine_host.h"
#include "check.h"
#if N_AXIS != 7
#error This case requires seven configured axes
#endif
int main(void)
{
    const parameter_words_t words[] = {{.x = true}, {.y = true}, {.z = true},
        {.a = true}, {.b = true}, {.c = true}, {.u = true}};
    const uint8_t expected[] = {1, 2, 4, 8, 16, 32, 64};
    for(unsigned i = 0; i < 7; i++) CHECK(gc_paramwords_to_axes(words[i]).mask == expected[i]);
    return EXIT_SUCCESS;
}
