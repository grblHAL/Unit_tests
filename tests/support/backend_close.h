#pragma once
#include "vfs.h"
/* Exercise backend lifetime directly, independently of the VFS dispatcher.
   Dispatcher close/lifetime behavior has separate integration tests. */
static inline void backend_close(vfs_file_t *file)
{
    ((const vfs_t *)file->fs)->fclose(file);
}
