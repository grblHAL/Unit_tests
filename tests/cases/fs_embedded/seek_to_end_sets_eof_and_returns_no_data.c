#include "support/embedded_seek_host.h"

int main(void)
{
    vfs_file_t *file = open_seek_fixture();
    CHECK(vfs_seek(file, 5) == 0);
    CHECK(vfs_tell(file) == 5 && vfs_eof(file));
    char byte = '!';
    CHECK(vfs_read(&byte, 1, 1, file) == 0);
    CHECK(byte == '!');
    vfs_close(file);
    return EXIT_SUCCESS;
}
