#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value;
    sys.var5399 = -1;
    CHECK(ngc_param_get(5399, &value)); NEAR(value, -1);
    sys.var5399 = 0;
    CHECK(ngc_param_get(5399, &value)); NEAR(value, 0);
    sys.var5399 = 7;
    CHECK(ngc_param_get(5399, &value)); NEAR(value, 7);
    return EXIT_SUCCESS;
}
