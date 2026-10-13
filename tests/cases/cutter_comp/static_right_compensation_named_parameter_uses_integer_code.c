#include "support/cutter_capture_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_cutter_capture();
    NEAR(read_named_parameter("_ccomp"), 400);
    CHECK(cutter_block("G42D2") == Status_OK);
    CHECK(cutter_enable_calls == 1);
    NEAR(read_named_parameter("_ccomp"), 420);
    CHECK(cutter_block("G40") == Status_OK);
    NEAR(read_named_parameter("_ccomp"), 400);
    return EXIT_SUCCESS;
}
