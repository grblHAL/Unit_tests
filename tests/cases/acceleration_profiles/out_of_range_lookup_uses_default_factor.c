#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); NEAR(gc_get_accel_factor(255), 1); NEAR(gc_get_accel_factor(5), 1);
    return EXIT_SUCCESS;
}
