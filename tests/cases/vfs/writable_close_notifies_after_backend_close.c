#include "support/vfs_operations_host.h"
static void changed_after_close(const vfs_t *fs) { CHECK(close_calls == 1); operation_changed(fs); }

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    vfs.on_fs_changed = changed_after_close;
    vfs_file_t *file = vfs_open("/store/program.nc", "w");
    CHECK(file && file->fs == &operation_fs && file->status.update);
    CHECK(strcmp(operation_path, "/program.nc") == 0 && strcmp(operation_mode, "w") == 0);
    CHECK(close_calls == 0 && change_calls == 0);
    vfs_close(file); CHECK(close_calls == 1 && change_calls == 1);
    vfs.on_fs_changed = NULL;
    file = vfs_open("/store/next.nc", "w");
    CHECK(file && file->fs == &operation_fs && file->status.update);
    CHECK(open_calls == 2 && strcmp(operation_path, "/next.nc") == 0);
    vfs_close(file);
    CHECK(close_calls == 2 && change_calls == 1);
    cleanup_operations();
    return EXIT_SUCCESS;
}
