#pragma once
#include "vfs.h"
/* Exercise backend lifetime directly. vfs_close has a separately tested known
   use-after-free; bypassing the dispatcher isolates backend behavior. */
static inline void backend_close(vfs_file_t *file)
{
    ((const vfs_t *)file->fs)->fclose(file);
}
