#include "support/catalog_report_host.h"
#include "check.h"

int main(void)
{
    prepare_catalog_report();
    CHECK(report_error_details(true) == Status_OK);
    CHECK(strncmp(engine_output, "\"Error Code in v1.1+\"", strlen("\"Error Code in v1.1+\"")) == 0);
    const char *first = strstr(engine_output, "\"1\",\"N/A\",\"first\"" ASCII_EOL);
    const char *second = strstr(engine_output, "\"2\",\"N/A\",\"\"" ASCII_EOL);
    const char *third = strstr(engine_output, "\"3\",\"N/A\",\"third\"" ASCII_EOL);
    CHECK(first != NULL && second != NULL && third != NULL);
    CHECK(first < second && second < third);
    return EXIT_SUCCESS;
}
