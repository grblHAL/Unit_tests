#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    close_nested_ram_level(2);
    nested_expect_text("F200\n");
    CHECK(grbl.on_line_number_assigned(0) == 2);
    close_nested_ram_level(1);
    nested_expect_text("G91\n");
    CHECK(grbl.on_line_number_assigned(0) == 2);
    close_nested_ram_level(0);
    CHECK(vfs_open("/ram/main", "r") == NULL);
    CHECK(vfs_open("/ram/sub", "r") == NULL);
    CHECK(vfs_open("/ram/leaf", "r") == NULL);
    return EXIT_SUCCESS;
}
