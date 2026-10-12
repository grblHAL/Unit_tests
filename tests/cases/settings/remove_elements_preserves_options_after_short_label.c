#include "support/settings_elements_host.h"
#include "check.h"

int main(void)
{
    prepare_setting_elements("Off,On,Auto");
    setting_remove_elements((setting_id_t)1001, 5, false);
    fprintf(stderr, "Option format after disabling On: %s; expected Off,N/A,Auto\n", element_format);
    CHECK(strcmp(element_format, "Off,N/A,Auto") == 0);
    return EXIT_SUCCESS;
}
