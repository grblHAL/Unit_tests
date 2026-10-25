#include "support/ram_macro_protocol_host.h"

int main(void)
{
    run_ram_root_protocol(
        "#1=99\n#29=72\n#30=73\n"
        "O10SUB\n#100=#29\n#101=#30\n#1=3\n#29=4\n#30=5\nO10ENDSUB\n"
        "O10CALL[1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][29][30]\n#110=#100\n#111=#101\n"
        "O10CALL[1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][1][29]\n#120=#100\n#121=#101\n#130=1\n");
    NEAR(ram_flow_parameter(110), 29);
    NEAR(ram_flow_parameter(111), 30);
    NEAR(ram_flow_parameter(120), 29);
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(29), 72);
    NEAR(ram_flow_parameter(30), 73);
    NEAR(ram_flow_parameter(130), 1);
    CHECK(ngc_call_level() == 0);
    /* The omitted final argument inherits the caller, just like other omitted locals. */
    float inherited = ram_flow_parameter(121);
    if(inherited != 73.0f)
        fprintf(stderr, "29-argument CALL: inherited #30=%g, expected73\n", (double)inherited);
    NEAR(inherited, 73);
    return EXIT_SUCCESS;
}
