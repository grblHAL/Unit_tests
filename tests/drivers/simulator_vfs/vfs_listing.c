#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); sim_put("/one.ngc", "M2"); CHECK(vfs_mkdir("/archive") == 0);
 vfs_dir_t *dir = vfs_opendir("/"); CHECK(dir); unsigned files = 0, folders = 0; vfs_dirent_t *entry;
 while((entry = vfs_readdir(dir))) {
  CHECK(strcmp(entry->name, ".") != 0 && strcmp(entry->name, "..") != 0);
  if(strcmp(entry->name, "one.ngc") == 0) { CHECK(entry->size == 2 && !entry->st_mode.directory); files++; }
  else if(strcmp(entry->name, "archive") == 0) { CHECK(entry->st_mode.directory); folders++; }
  else CHECK(false);
 }
 vfs_closedir(dir); CHECK(files == 1 && folders == 1);
 CHECK(vfs_opendir("/absent") == NULL); CHECK(vfs_unlink("/one.ngc") == 0 && vfs_rmdir("/archive") == 0);
 sim_finish("/"); return 0;
}
