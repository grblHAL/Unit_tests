#include "support/catalog_report_host.h"
#include "support/calloc_failure_host.h"
int main(void)
{
    prepare_catalog_report();
    // A sender must still be able to decode failures when the sort buffer cannot be allocated.
    fail_calloc = true;
    CHECK(report_error_details(false) == Status_OK);
    fail_calloc = false;
    CHECK(failed_calloc_calls == 1);
    CHECK(strstr(engine_output, "[ERRORCODE:1||first]") != NULL);
    CHECK(strstr(engine_output, "[ERRORCODE:2||]") != NULL);
    CHECK(strstr(engine_output, "[ERRORCODE:3||third]") != NULL);
    unsigned rows = 0;
    for(const char *cursor = engine_output; (cursor = strstr(cursor, "[ERRORCODE:")); cursor++) rows++;
    CHECK(rows == 3);
    engine_output[0] = '\0';
    CHECK(report_error_details(false) == Status_OK);
    CHECK(strncmp(engine_output, "[ERRORCODE:1||first]", strlen("[ERRORCODE:1||first]")) == 0);
    CHECK(failed_calloc_calls == 1);
    return EXIT_SUCCESS;
}
