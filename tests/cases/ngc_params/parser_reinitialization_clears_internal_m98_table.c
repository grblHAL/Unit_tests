#include "support/m98_prescan_host.h"
#include "check.h"

int main(void)
{
    prepare_m98_prescan();
    CHECK(macro_block("M98P10") == Status_OK);
    file_position = 4;
    CHECK(macro_block("O10") == Status_OK);
    CHECK(gc_macro_get_pos(10, hal.stream.file) == 4);
    gc_init(false);
    CHECK(gc_macro_get_pos(10, hal.stream.file) == 0);
    close_flow_file();
    return EXIT_SUCCESS;
}
