#include "vfs_host.h"
char sim_backing[64];
unsigned sim_mounts, sim_changes;
static void mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{ CHECK(path && strcmp(fs->fs_name, "PosixFs") == 0 && fs->removable && !mode.mode); sim_mounts++; }
static void changed(const vfs_t *fs) { CHECK(strcmp(fs->fs_name, "PosixFs") == 0); sim_changes++; }
bool stream_await_tx_clear(const io_stream_t *stream) { CHECK(stream == &hal.stream); return true; }
void sim_prepare(const char *mount)
{
 snprintf(sim_backing, sizeof(sim_backing), "store-%u", (unsigned)getpid());
#ifdef _WIN32
 CHECK(mkdir(sim_backing) == 0);
#else
 CHECK(mkdir(sim_backing, 0755) == 0);
#endif
 vfs.on_mount = mounted; vfs.on_fs_changed = changed;
 CHECK(fs_posix_mount(mount, sim_backing)); CHECK(sim_mounts == 1);
}
void sim_finish(const char *mount) { CHECK(vfs_unmount(NULL, mount)); CHECK(rmdir(sim_backing) == 0); }
void sim_put(const char *path, const char *text)
{
 vfs_file_t *file = vfs_open(path, "wb"); CHECK(file);
 CHECK(vfs_write(text, 1, strlen(text), file) == strlen(text)); vfs_close(file);
}
void sim_expect(const char *path, const char *text)
{
 char buffer[128] = {0}; CHECK(strlen(text) < sizeof(buffer));
 vfs_file_t *file = vfs_open(path, "rb"); CHECK(file);
 CHECK(vfs_read(buffer, 1, sizeof(buffer) - 1, file) == strlen(text)); CHECK(strcmp(buffer, text) == 0);
 CHECK(vfs_eof(file)); vfs_close(file);
}
