#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"
int main(void)
{
    engine_parser_prepare();
    char text[NGC_MAX_PARAM_LENGTH + 4];
    text[0] = '<';
    memset(text + 1, 'A', NGC_MAX_PARAM_LENGTH + 1);
    text[NGC_MAX_PARAM_LENGTH + 2] = '>';
    text[NGC_MAX_PARAM_LENGTH + 3] = '\0';
    /* Extra storage keeps this rejection test safe on the defective core. */
    char name[NGC_MAX_PARAM_LENGTH + 2] = {0};
    uint_fast8_t pos = 0;
    status_code_t status = ngc_read_name(text, &pos, name);
    fprintf(stderr, "name status=%u, length=%u, maximum=%u\n",
            (unsigned)status, (unsigned)strlen(name), (unsigned)NGC_MAX_PARAM_LENGTH);
    CHECK(status == Status_FlowControlSyntaxError);
    return EXIT_SUCCESS;
}
