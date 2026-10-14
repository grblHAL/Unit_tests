#include "vfs.h"
#include <string.h>
#include "check.h"

/* Observe only this call's output allocation, so the known missing return does
   not leave a secondary leak diagnostic after the correct pointer assertion. */
static bool observe_root_buffer;
static void *root_buffer;
void *__real_malloc(size_t size);
void __real_free(void *ptr);
void *__wrap_malloc(size_t size)
{
    void *ptr = __real_malloc(size);
    if(observe_root_buffer) root_buffer = ptr;
    return ptr;
}
void __wrap_free(void *ptr)
{
    if(ptr == root_buffer) root_buffer = NULL;
    __real_free(ptr);
}
int main(void)
{
    observe_root_buffer = true;
    char *path = vfs_getcwd(NULL, 0);
    observe_root_buffer = false;
    if(!path && root_buffer) {
        __real_free(root_buffer);
        root_buffer = NULL;
    }
    CHECK(path != NULL);
    CHECK(strcmp(path, "/") == 0);
    free(path);
    return EXIT_SUCCESS;
}
