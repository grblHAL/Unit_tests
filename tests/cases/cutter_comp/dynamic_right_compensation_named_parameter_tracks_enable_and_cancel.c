#include "support/cutter_capture_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_cutter_capture();
    NEAR(read_named_parameter("_ccomp"), 400);
    CHECK(cutter_block("G42.1D6") == Status_OK);
    CHECK(cutter_enable_calls == 1);
    NEAR(read_named_parameter("_ccomp"), 421);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X10F100") == Status_OK);
    CHECK(!HOST_PARSER_FLAGS.ccomp_off);
    fprintf(stderr, "cancelled compensation parameter: %g\n", (double)read_named_parameter("_ccomp"));
    NEAR(read_named_parameter("_ccomp"), 400);
    return EXIT_SUCCESS;
}
