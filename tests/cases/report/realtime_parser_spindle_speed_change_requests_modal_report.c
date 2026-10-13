#include "support/parser_change_report_host.h"

int main(void)
{
    prepare_parser_change_report();
    CHECK(named_parameter_block("S1200") == Status_OK);
    expect_parser_change_report();
    CHECK(named_parameter_block("S2400") == Status_OK);
    expect_parser_change_report();
    return EXIT_SUCCESS;
}
