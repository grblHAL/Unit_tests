#include "support/vfs_drive_format_host.h"
static int stat_before_format(const char *path, vfs_stat_t *st)
{
    CHECK(strcmp(path, "/jobs") == 0);
    memset(st, 0, sizeof(*st));
    st->st_mode.directory = true;
    return 0;
}
static char routed_path[64];
static int stat_after_format(const char *path, vfs_stat_t *st)
{
    CHECK(strlen(path) < sizeof(routed_path));
    strcpy(routed_path, path);
    memset(st, 0, sizeof(*st));
    return 0;
}
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    // Frontend-only directories: no backend chdir/getcwd callback pair.
    format_fs.fstat = stat_before_format;
    CHECK(vfs_chdir("/store/jobs") == 0);
    CHECK(vfs_drive_format(drive) == 0);
    char directory[128];
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory);
    CHECK(strcmp(directory, "/store") == 0);
    format_fs.fstat = stat_after_format;
    vfs_stat_t st;
    CHECK(vfs_stat("new.nc", &st) == 0);
    fprintf(stderr, "Formatted drive routes relative file as %s\n", routed_path);
    CHECK(strcmp(routed_path, "/new.nc") == 0);
    CHECK(strcmp(format_events, "TUFRM") == 0);
    CHECK(format_calls == 1 && format_mount_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
