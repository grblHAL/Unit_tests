#include "support/macro_parser_host.h"
int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66P200X12") == Status_OK);
    status_code_t actual = macro_block("G65X7");
    fprintf(stderr, "G65 without P, G66 armed: status=%u callbacks=%u macro=%lu\n",
        (unsigned)actual, macro_calls, (unsigned long)called_macro);
    CHECK(actual == Status_GcodeValueWordMissing);
    CHECK(macro_calls == 0 && ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
