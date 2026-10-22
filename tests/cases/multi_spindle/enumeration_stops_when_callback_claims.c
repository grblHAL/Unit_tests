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

static bool visit_all(spindle_info_t *spindle, void *data)
{
    CHECK(data == &enumerated);
    CHECK(spindle->id == (spindle_id_t)enumerated);
    CHECK(spindle->ref_id == 10 * (enumerated + 1));
    CHECK(spindle->hal != NULL);
    CHECK(spindle->is_current == (enumerated == 0));
    enumerated++;
    return false;
}

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enumerate_spindles(stop_after_two, &enumerated));
    CHECK(enumerated == 2);
    enumerated = 0;
    CHECK(!spindle_enumerate_spindles(visit_all, &enumerated));
    CHECK(enumerated == 3);
    CHECK(spindle_get_default() == 0);
    return EXIT_SUCCESS;
}
