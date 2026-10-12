#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"
static inline void create_file(const char *name, const char *data)
{
    vfs_file_t *file = vfs_open(name, "w");
    CHECK(file != NULL);
    size_t length = strlen(data);
    CHECK(vfs_write(data, 1, length, file) == length);
    backend_close(file);
}

int main(void)
{
    fs_ram_mount();
    CHECK(vfs_mount_set_mode("/ram", (vfs_st_mode_t){ .directory = true }));
    create_file("/ram/first", "abc");
    create_file("/ram/middle", "12345");
    create_file("/ram/last", "xy");
    vfs_free_t *space = vfs_fgetfree("/ram/");
    CHECK(space != NULL && space->used == 10);
    CHECK(space->size == 10);
    CHECK(vfs_unlink("/ram/middle") == 0);
    CHECK(vfs_fgetfree("/ram/")->used == 5);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/first", &st) == 0 && st.st_size == 3);
    CHECK(vfs_stat("/ram/last", &st) == 0 && st.st_size == 2);
    CHECK(vfs_unlink("/ram/first") == 0);
    CHECK(vfs_fgetfree("/ram/")->used == 2);
    CHECK(vfs_unlink("/ram/last") == 0);
    CHECK(vfs_fgetfree("/ram/")->used == 0);
    CHECK(vfs_opendir("/ram") == NULL);
    return EXIT_SUCCESS;
}
