#include "support/boot_host.h"

static void configure_filesystems(settings_t *current)
{
    CHECK(current == &settings);
    hal.driver_cap.sd_card = 1;
    hal.driver_cap.littlefs = 0;
}

int main(void)
{
    boot_during_setup = configure_filesystems;
    CHECK(grbl_enter() == 0);
    const setting_detail_t *detail = setting_get_details(Setting_FSOptions, NULL);
    CHECK(detail != NULL);
    CHECK(strcmp(detail->format, "Auto mount SD card,N/A,Hierarchical listing") == 0);
    return EXIT_SUCCESS;
}
