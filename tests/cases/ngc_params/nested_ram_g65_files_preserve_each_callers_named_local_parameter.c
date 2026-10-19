#include "support/ram_macro_protocol_host.h"
int main(void)
{
    ram_capture_named = true;
    run_ram_macro_protocol("#1=3\n#<note>=3\nG65P10A5\n", "#<note>=9\nG65P20A7\n", "#<note>=17\n");
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    NEAR(ram_return_named[0], 3); NEAR(ram_return_named[1], 9); NEAR(ram_return_named[2], 17);
    float parent; CHECK(ngc_named_param_get("note", &parent)); NEAR(parent, 3);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
