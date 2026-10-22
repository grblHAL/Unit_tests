#include "support/vfs_drive_format_host.h"

static void root_unmounted(const char *path)
{
    CHECK(strcmp(path, "/") == 0);
    format_event('U');
}
static void root_mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{
    CHECK(strcmp(path, "/") == 0 && fs == &format_fs && mode.directory);
    format_event('M');
}
int main(void)
{
    engine_prepare();
    const vfs_t *safe_backend = vfs_get_drive("/")->fs;
    hal.stream.get_tx_buffer_count = format_tx_count;
    format_fs = (vfs_t){.fs_name = "root", .format = format_backend,
        .device_mount = format_mount_device, .fgetfree = format_getfree};
    CHECK(vfs_mount(&format_device, "/", &format_fs, (vfs_st_mode_t){.directory = true}));
    vfs.on_unmount = root_unmounted;
    vfs.on_mount = root_mounted;
    vfs_drive_t *drive = vfs_get_drive("/");
    CHECK(drive->fs == &format_fs);
    format_result = -7;
    CHECK(vfs_drive_format(drive) == -7 && vfs_errno == -7);
    CHECK(strcmp(format_events, "TUFD") == 0);
    CHECK(format_calls == 1 && format_mount_calls == 1);
    drive = vfs_get_drive("/");
    CHECK(drive->fs == safe_backend);
    CHECK(drive->mode.read_only && drive->mode.hidden);
    CHECK(vfs_drive_getfree(drive) == NULL);
    char directory[16];
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory);
    CHECK(strcmp(directory, "/") == 0);
    CHECK(vfs_unlink("part.nc") == -1);

    CHECK(vfs_mount(&format_device, "/", &format_fs, (vfs_st_mode_t){.directory = true}));
    drive = vfs_get_drive("/");
    CHECK(drive->fs == &format_fs && !drive->mode.read_only);
    vfs_free_t *space = vfs_drive_getfree(drive);
    CHECK(space != NULL && space->size == 8192 && space->used == 512);
    CHECK(strcmp(format_events, "TUFDM") == 0);
    CHECK(vfs_unmount(&format_device, "/"));
    vfs.on_unmount = NULL;
    vfs.on_mount = NULL;
    return EXIT_SUCCESS;
}
