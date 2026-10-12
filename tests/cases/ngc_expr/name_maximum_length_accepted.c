#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char text[NGC_MAX_PARAM_LENGTH + 3];
    text[0] = '<';
    memset(text + 1, 'A', NGC_MAX_PARAM_LENGTH);
    text[NGC_MAX_PARAM_LENGTH + 1] = '>';
    text[NGC_MAX_PARAM_LENGTH + 2] = '\0';
    char name[NGC_MAX_PARAM_LENGTH + 1];
    uint_fast8_t pos = 0;
    CHECK(ngc_read_name(text, &pos, name) == Status_OK);
    CHECK(pos == strlen(text));
    CHECK(strlen(name) == NGC_MAX_PARAM_LENGTH);
    CHECK(name[0] == 'a');
    return EXIT_SUCCESS;
}
