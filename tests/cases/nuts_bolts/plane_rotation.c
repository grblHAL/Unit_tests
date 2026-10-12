#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    coord_data_t pt = {.values = {1, 0, 7}};
    plane_t xy = {.axis_0 = 0, .axis_1 = 1, .axis_linear = 2};
    rotate(&pt, xy, (float)M_PI / 2); NEAR(pt.values[0], 0); NEAR(pt.values[1], 1); NEAR(pt.values[2], 7);
    rotate(&pt, xy, -(float)M_PI / 2); NEAR(pt.values[0], 1); NEAR(pt.values[1], 0);
    return EXIT_SUCCESS;
}
