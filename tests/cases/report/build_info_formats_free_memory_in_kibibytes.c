#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.get_free_mem = build_free_memory;
    build_report(true);
    CHECK(strstr(engine_output, "[FREE MEMORY:12K]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
