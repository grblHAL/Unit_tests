#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); CHECK(vfs_mkdir("/archive") == 0); sim_put("/archive/part.ngc", "G1X10\nM2\n");
 vfs_dir_t *dir = vfs_opendir("/archive"); CHECK(dir); vfs_dirent_t *entry = vfs_readdir(dir);
 CHECK(entry && strcmp(entry->name, "part.ngc") == 0); size_t size = entry->size; int error = vfs_errno;
 CHECK(vfs_readdir(dir) == NULL); vfs_closedir(dir);
 CHECK(vfs_unlink("/archive/part.ngc") == 0 && vfs_rmdir("/archive") == 0); sim_finish("/");
 fprintf(stderr, "nested size=%zu errno=%d\n", size, error); CHECK(size == 9 && error == 0); return 0;
}
