#include "support/m98_prescan_host.h"
int main(void)
{
    prepare_m98_prescan();
    CHECK(macro_block("M98P10") == Status_OK);
    CHECK(macro_block("M98P20") == Status_OK);
    CHECK(macro_block("M98P30") == Status_OK);
    CHECK(macro_block("M98P10L2") == Status_OK);
    file_position = 1;
    CHECK(macro_block("O10") == Status_OK);
    file_position = 4;
    CHECK(macro_block("O20") == Status_OK);
    file_position = 8;
    CHECK(macro_block("O30") == Status_OK);
    CHECK(gc_macro_get_pos(10, hal.stream.file) == 1);
    CHECK(gc_macro_get_pos(20, hal.stream.file) == 4);
    CHECK(gc_macro_get_pos(30, hal.stream.file) == 8);
    CHECK(macro_calls == 0);
    close_flow_file();
    return EXIT_SUCCESS;
}
