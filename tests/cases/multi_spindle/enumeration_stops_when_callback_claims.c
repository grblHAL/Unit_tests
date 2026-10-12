#include "support/multi_spindle_host.h"
#include "report.h"
#include "check.h"
static unsigned enumerated;
static bool stop_after_two(spindle_info_t *spindle, void *data)
{
    CHECK(data == &enumerated);
    CHECK(spindle->id == (spindle_id_t)enumerated);
    enumerated++;
    return enumerated == 2;
}

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enumerate_spindles(stop_after_two, &enumerated));
    CHECK(enumerated == 2);
    return EXIT_SUCCESS;
}
