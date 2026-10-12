#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char first[] = "G51X2";
    CHECK(gc_execute_block(first) == Status_OK);
    char second[] = "G51Y3";
    CHECK(gc_execute_block(second) == Status_OK);
    NEAR(gc_get_scaling()[X_AXIS], 2);
    NEAR(gc_get_scaling()[Y_AXIS], 3);
    NEAR(gc_get_scaling()[Z_AXIS], 1);
    return EXIT_SUCCESS;
}
