#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = " My Name "; char lookup[] = "myname"; float value; CHECK(ngc_named_param_set(name, 12.5f)); CHECK(ngc_named_param_get(lookup, &value)); NEAR(value, 12.5f);
    return EXIT_SUCCESS;
}
