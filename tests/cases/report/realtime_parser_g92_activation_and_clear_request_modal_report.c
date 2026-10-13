#include "support/parser_change_report_host.h"

int main(void)
{
    prepare_parser_change_report();
    CHECK(named_parameter_block("G92X3") == Status_OK);
    expect_parser_change_report();
    CHECK(named_parameter_block("G92.1") == Status_OK);
    expect_parser_change_report();
    return EXIT_SUCCESS;
}
