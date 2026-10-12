#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    hal.stream.report.flags.value = 0;
    char scale[] = "G51X2";
    CHECK(gc_execute_block(scale) == Status_OK);
    CHECK(hal.stream.report.flags.value & Report_Scaling);
    return EXIT_SUCCESS;
}
