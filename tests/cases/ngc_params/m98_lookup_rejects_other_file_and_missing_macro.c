#include "support/m98_prescan_host.h"
#include "check.h"

int main(void)
{
    prepare_m98_prescan();
    CHECK(macro_block("M98P10") == Status_OK);
    file_position = 4;
    CHECK(macro_block("O10") == Status_OK);
    vfs_file_t other_file = {0};
    CHECK(gc_macro_get_pos(10, &other_file) == 0);
    CHECK(gc_macro_get_pos(20, hal.stream.file) == 0);
    CHECK(gc_macro_get_pos(10, hal.stream.file) == 4);
    close_flow_file();
    return EXIT_SUCCESS;
}
