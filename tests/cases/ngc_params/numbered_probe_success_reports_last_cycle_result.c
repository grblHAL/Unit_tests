#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value;
    sys.flags.probe_succeeded = false;
    CHECK(ngc_param_get(5070, &value)); NEAR(value, 0);
    sys.flags.probe_succeeded = true;
    CHECK(ngc_param_get(5070, &value)); NEAR(value, 1);
    sys.flags.probe_succeeded = false;
    CHECK(ngc_param_get(5070, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
