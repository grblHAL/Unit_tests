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
static uint32_t available_memory(void) { return 4096; }

int main(void)
{
    fs_ram_mount();
    hal.get_free_mem = available_memory;
    create_file("/ram/job", "hello");
    vfs_free_t *space = vfs_fgetfree("/ram/");
    CHECK(space != NULL);
    CHECK(space->used == 5);
    CHECK(space->size == 4096);
    return EXIT_SUCCESS;
}
