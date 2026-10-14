#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,false,false);
    root_found = true;
    const char *path = vfs_locate_file("abcdefghijklmnopqrst");
    CHECK(path && strcmp(path,"/abcdefghijklmnopqrst") == 0);
    CHECK(lookup_count == 1);
    unmount_lookup_sources(true,false,false);
    return EXIT_SUCCESS;
}
