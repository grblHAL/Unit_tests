#include "pulloff_host.h"
int main(void)
{
    prepare_pulloff();
    settings_changed_ptr old_changed = grbl.on_settings_changed;
    on_report_options_ptr old_report = grbl.on_report_options;
#ifdef FAIL_ALLOCATION
    allocation_ok = false;
#else
    registration_ok = false;
#endif
    initialize_pulloff();
    CHECK(details == NULL && saves == 0 && updates == 0);
    CHECK(grbl.on_settings_changed == old_changed && grbl.on_report_options == old_report);
    return 0;
}
