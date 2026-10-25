#pragma once
#include "check.h"
/* Older CORE mounts return void; retain their existing lifecycle assertions. */
#ifdef HOST_FS_MOUNT_RESULT_API
#define CHECK_MOUNT_RESULT(operation, expected) CHECK((operation) == (expected))
#else
#define CHECK_MOUNT_RESULT(operation, expected) ((void)(operation))
#endif
