#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,false,false);
     CHECK(vfs_locate_file("/missing.nc") == NULL);
    CHECK(lookup_count == 1);
    unmount_lookup_sources(true,false,false);
    return EXIT_SUCCESS;
}
