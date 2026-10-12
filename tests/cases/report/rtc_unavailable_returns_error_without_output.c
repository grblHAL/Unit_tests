#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_time() == Status_InvalidStatement);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
