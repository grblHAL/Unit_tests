#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); CHECK(vfs_mkdir("/jobs") == 0); CHECK(vfs_chdir("/jobs") == 0);
 char cwd[128]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) && strcmp(cwd, "/jobs") == 0);
 sim_put("part.ngc", "M2"); sim_expect("./part.ngc", "M2"); CHECK(vfs_chdir("..") == 0);
 CHECK(vfs_getcwd(cwd, sizeof(cwd)) && strcmp(cwd, "/") == 0);
 const char *long_dir = "/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
 CHECK(vfs_mkdir(long_dir) == 0 && vfs_chdir(long_dir) == 0);
 CHECK(vfs_getcwd(cwd, sizeof(cwd)) && strcmp(cwd, long_dir) == 0);
 sim_put("end.ngc", "M30"); sim_expect("end.ngc", "M30"); CHECK(vfs_unlink("end.ngc") == 0);
 CHECK(vfs_chdir("/") == 0 && vfs_rmdir(long_dir) == 0);
 CHECK(vfs_unlink("/jobs/part.ngc") == 0 && vfs_rmdir("/jobs") == 0); sim_finish("/"); return 0;
}
