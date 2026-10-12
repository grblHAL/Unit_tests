#include "support/named_parameter_host.h"
#include "support/css_host.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    grbl.on_execute_realtime = protocol_execute_noop;
    CHECK(named_parameter_block("M53P0") == Status_OK);
    NEAR(read_named_parameter("_feed_hold"), 0);
    CHECK(named_parameter_block("M53P1") == Status_OK);
    NEAR(read_named_parameter("_feed_hold"), 1);
    return EXIT_SUCCESS;
}
