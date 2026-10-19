#include "support/macro_parser_host.h"
int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66P200X12") == Status_OK);
    CHECK(macro_calls == 0);
    CHECK(macro_block("G65P100X7") == Status_OK);
    fprintf(stderr, "G65 with G66 armed: calls=%u macro=%lu repeat=%lu\n", macro_calls,
        (unsigned long)called_macro, (unsigned long)macro_repeats);
    CHECK(macro_calls == 1 && called_macro == 100);
    CHECK(macro_repeats == 1);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
