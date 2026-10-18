#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    stream_reposition(nested_ram_files[2], 0, 42);
    CHECK(grbl.on_line_number_assigned(0) == 42);
    nested_expect_text("G21\n");
    CHECK(grbl.on_line_number_assigned(0) == 43);
    close_nested_ram_level(2);
    nested_expect_text("F200\n");
    CHECK(grbl.on_line_number_assigned(0) == 2);
    close_nested_ram_level(1);
    nested_expect_text("G91\n");
    close_nested_ram_level(0);
    return EXIT_SUCCESS;
}
