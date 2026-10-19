#include "support/named_parameter_host.h"
int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("#1=3") == Status_OK);
    CHECK(named_parameter_block("#2=7") == Status_OK);
    CHECK(named_parameter_block("#100=#[2-0.00005]") == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 7);
    return EXIT_SUCCESS;
}
