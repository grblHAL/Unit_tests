#include "support/embedded_allocation_host.h"
#include "support/mount_result_host.h"
static unsigned mount_notifications;
static void mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{
    (void)path; (void)fs; (void)mode;
    mount_notifications++;
    vfs_file_t *file = vfs_open("/embedded/first", "r");
    char byte;
    CHECK(file && vfs_read(&byte, 1, 1, file) == 1 && byte == 'a');
    vfs_close(file);
}
int main(void)
{
    vfs_st_mode_t root_before = vfs_get_drive("/")->mode;
    vfs.on_mount = mounted;
    begin_embedded_heap_failure(1);
    CHECK_MOUNT_RESULT(fs_embedded_mount(heap_files), false);
    end_embedded_heap_failure(1);
    CHECK(mount_notifications == 0);
    vfs_st_mode_t root_after = vfs_get_drive("/")->mode;
    bool root_preserved = root_before.hidden == root_after.hidden &&
        root_before.read_only == root_after.read_only && root_before.directory == root_after.directory;
    CHECK_MOUNT_RESULT(fs_embedded_mount(heap_files), true);
    CHECK(mount_notifications == 1);
    check_embedded_directory(false);
    vfs_file_t *file = vfs_open("/embedded/first", "r");
    char byte;
    CHECK(file && vfs_read(&byte, 1, 1, file) == 1 && byte == 'a');
    vfs_close(file);
    vfs.on_mount = NULL;
    fprintf(stderr, "Failed embedded mount root hidden=%u->%u; one readable mount on retry\n",
        root_before.hidden, root_after.hidden);
    CHECK(root_preserved);
    return EXIT_SUCCESS;
}
