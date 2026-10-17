#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
int main(void)
{
    engine_parser_prepare();
    CHECK(NGC_MAX_PARAM_LENGTH == 80);
    char name[NGC_MAX_PARAM_LENGTH + 1];
    memset(name, 'a', sizeof(name) - 1); name[sizeof(name) - 1] = 0;
    char assign[128] = "#<";
    strcat(assign, name); strcat(assign, ">=12.5");
    CHECK(gc_execute_block(assign) == Status_OK);
    float value;
    CHECK(ngc_named_param_get(name, &value)); NEAR(value, 12.5f);
    char reference[128] = "#100=[#<";
    strcat(reference, name); strcat(reference, ">*2]");
    CHECK(gc_execute_block(reference) == Status_OK);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 25);
    return EXIT_SUCCESS;
}
