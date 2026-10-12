#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true); CHECK(css_block("G18") == Status_OK);
    CHECK(css_block("G70X10Z20F100") == Status_GcodeValueWordMissing);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
