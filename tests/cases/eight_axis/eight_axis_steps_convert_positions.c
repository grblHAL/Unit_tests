#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    int32_t steps[N_AXIS];
    float position[N_AXIS];
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        steps[axis] = (int32_t)(80 * (axis + 1));
    system_convert_array_steps_to_mpos(position, steps);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(position[axis], (float)(axis + 1));
    return EXIT_SUCCESS;
}
