#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    sys.position[6] = 560;
    sys.position[7] = 640;
    char u[] = "_u", v[] = "_v";
    float value;
    CHECK(ngc_named_param_get(u, &value));
    NEAR(value, 7);
    CHECK(ngc_named_param_get(v, &value));
    NEAR(value, 8);
    return EXIT_SUCCESS;
}
