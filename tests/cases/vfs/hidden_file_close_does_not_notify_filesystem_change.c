#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){.hidden = true});
    vfs_file_t *file = vfs_open("/store/program.nc", "w");
    CHECK(file && !file->status.update); vfs_close(file);
    CHECK(close_calls == 1 && change_calls == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
