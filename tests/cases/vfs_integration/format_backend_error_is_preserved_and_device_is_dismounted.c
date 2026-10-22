#include "support/vfs_drive_format_host.h"
static char recovered_path[64];
static int format_directory(const char *path, vfs_stat_t *st)
{
    CHECK(strlen(path) < sizeof(recovered_path));
    strcpy(recovered_path, path);
    memset(st, 0, sizeof(*st));
    st->st_mode.directory = strcmp(path, "/jobs") == 0;
    return 0;
}
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_fs.fstat = format_directory;
    CHECK(vfs_chdir("/store/jobs") == 0);
    format_result = -7;
    CHECK(vfs_drive_format(drive) == -7);
    CHECK(vfs_errno == -7);
    CHECK(strcmp(format_events,"TUFD") == 0);
    CHECK(format_mount_calls == 1);
    char directory[128];
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory);
    CHECK(strcmp(directory, "/") == 0);

    format_result = 0;
    CHECK(vfs_drive_format(drive) == 0);
    CHECK(strcmp(format_events, "TUFDTUFRM") == 0);
    CHECK(format_calls == 2 && format_mount_calls == 2);
    CHECK(vfs_chdir("/store/jobs") == 0);
    vfs_stat_t st;
    CHECK(vfs_stat("part.nc", &st) == 0);
    CHECK(strcmp(recovered_path, "/jobs/part.nc") == 0);
    CHECK(!st.st_mode.directory);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
