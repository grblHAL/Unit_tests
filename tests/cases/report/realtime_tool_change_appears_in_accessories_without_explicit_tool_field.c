#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    HOST_PARSER_FLAGS.tool_change = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:T>") != NULL);
    CHECK(strstr(engine_output, "|T:") == NULL);
    return EXIT_SUCCESS;
}
