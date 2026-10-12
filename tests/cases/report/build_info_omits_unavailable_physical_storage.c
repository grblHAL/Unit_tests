#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    nvs_buffer_get_physical()->type = NVS_None;
    build_report(true);
    CHECK(strstr(engine_output, "[NVS STORAGE:") == NULL);
    return EXIT_SUCCESS;
}
