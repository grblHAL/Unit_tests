#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(gc_coord_system_to_str((coord_system_id_t)0), "G54") == 0);
    CHECK(strcmp(gc_coord_system_to_str((coord_system_id_t)5), "G59") == 0);
    return EXIT_SUCCESS;
}
