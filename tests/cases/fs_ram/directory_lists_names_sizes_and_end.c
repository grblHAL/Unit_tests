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
    create_file("/ram/first", "abc");
    create_file("/ram/second", "12345");
    vfs_dir_t *dir = vfs_opendir("/ram");
    CHECK(dir != NULL);
    bool first = false, second = false;
    unsigned count = 0;
    vfs_dirent_t *entry;
    while((entry = vfs_readdir(dir))) {
        CHECK(!entry->st_mode.directory);
        if(strcmp(entry->name, "/first") == 0) {
            CHECK(!first); first = true; CHECK(entry->size == 3);
        } else {
            CHECK(strcmp(entry->name, "/second") == 0);
            CHECK(!second); second = true; CHECK(entry->size == 5);
        }
        count++;
    }
    CHECK(first && second && count == 2);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    return EXIT_SUCCESS;
}
