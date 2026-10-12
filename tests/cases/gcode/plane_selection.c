#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char zx[] = "G18"; CHECK(gc_execute_block(zx) == Status_OK); CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    char yz[] = "G19"; CHECK(gc_execute_block(yz) == Status_OK); CHECK(gc_state.modal.plane_select == PlaneSelect_YZ);
    char xy[] = "G17"; CHECK(gc_execute_block(xy) == Status_OK); CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    return EXIT_SUCCESS;
}
