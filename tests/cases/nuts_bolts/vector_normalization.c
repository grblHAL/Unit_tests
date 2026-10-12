#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    float vector[N_AXIS] = {3, 4, 0};
    NEAR(convert_delta_vector_to_unit_vector(vector), 5);
    NEAR(vector[0], .6f); NEAR(vector[1], .8f); NEAR(vector[2], 0);
    float negative[N_AXIS] = {-3, 0, -4};
    NEAR(convert_delta_vector_to_unit_vector(negative), 5);
    NEAR(negative[0], -.6f); NEAR(negative[2], -.8f);
    return EXIT_SUCCESS;
}
