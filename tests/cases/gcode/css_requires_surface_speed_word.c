#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96") == Status_GcodeValueWordMissing);
    return EXIT_SUCCESS;
}
