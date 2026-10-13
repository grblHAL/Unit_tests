#include "support/embedded_seek_host.h"

int main(void)
{
    vfs_file_t *file = open_seek_fixture();
    CHECK(vfs_seek(file, 5) == 0 && vfs_eof(file));
    CHECK(vfs_seek(file, 0) == 0);
    CHECK(vfs_tell(file) == 0 && !vfs_eof(file));
    char data[6] = {0};
    CHECK(vfs_read(data, 1, 5, file) == 5);
    CHECK(strcmp(data, "hello") == 0);
    CHECK(vfs_eof(file));
    vfs_close(file);
    return EXIT_SUCCESS;
}
