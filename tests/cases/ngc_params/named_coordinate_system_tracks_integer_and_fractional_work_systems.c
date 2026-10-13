#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    const char *commands[] = {"G54", "G55", "G56", "G57", "G58", "G59", "G59.1", "G59.2", "G59.3"};
    const float codes[] = {540, 550, 560, 570, 580, 590, 591, 592, 593};
    for(unsigned i = 0; i < 9; i++) {
        CHECK(named_parameter_block(commands[i]) == Status_OK);
        NEAR(read_named_parameter("_coord_system"), codes[i]);
    }
    return EXIT_SUCCESS;
}
