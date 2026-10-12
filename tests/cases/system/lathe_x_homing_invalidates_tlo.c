#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.mode = Mode_Lathe;
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    system_clear_tlo_reference((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(sys.tlo_reference_set.mask == 0);
    return EXIT_SUCCESS;
}
