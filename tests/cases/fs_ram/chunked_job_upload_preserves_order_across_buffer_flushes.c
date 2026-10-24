#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    static uint8_t program[5159], actual[5159];
    /* Consecutive short packets share the buffer before larger packets flush it. */
    const size_t chunks[] = {6, 7, 1024, 17, 4096, 9};
    for(size_t i = 0; i < sizeof(program); i++) program[i] = (uint8_t)(i * 37 + i / 71);
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/chunked-job", "w");
    CHECK(file != NULL);
    size_t offset = 0;
    for(unsigned i = 0; i < sizeof(chunks) / sizeof(chunks[0]); i++) {
        CHECK(vfs_write(program + offset, 1, chunks[i], file) == chunks[i]);
        offset += chunks[i];
    }
    CHECK(offset == sizeof(program));
    vfs_close(file);
    file = vfs_open("/ram/chunked-job", "r");
    CHECK(file != NULL);
    /* Unsupported preallocation must preserve the already uploaded program. */
    CHECK(vfs_truncate(file, sizeof(program) + 1) == -1);
    offset = 0;
    while(!vfs_eof(file)) {
        size_t count = vfs_read(actual + offset, 1, 23, file);
        CHECK(count > 0 && count <= sizeof(actual) - offset);
        offset += count;
    }
    CHECK(offset == sizeof(program) && vfs_tell(file) == sizeof(program));
    CHECK(memcmp(actual, program, sizeof(program)) == 0);
    CHECK(vfs_seek(file, 1030) == 0);
    CHECK(vfs_read(actual, 1, 40, file) == 40);
    CHECK(memcmp(actual, program + 1030, 40) == 0);
    vfs_close(file);
    CHECK(vfs_open("/ram/chunked-job", "r") == NULL);
    return EXIT_SUCCESS;
}
