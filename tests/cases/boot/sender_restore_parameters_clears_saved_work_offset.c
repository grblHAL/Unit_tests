#include "support/boot_host.h"
#include "nvs_buffer.h"
static bool saw_work_offset;
static void observe_offset_before_restore(void)
{
    if(boot_reads == sizeof("G10L2P1X-12.5\n") - 1) {
        coord_system_data_t offset;
        CHECK(settings_read_coord_data(CoordinateSystem_G54, &offset));
        NEAR(offset.coord.x, -12.5f);
        saw_work_offset = true;
    }
}
int main(void)
{
    boot_program = "G10L2P1X-12.5\n$RST=#\n";
    boot_before_read = observe_offset_before_restore;
    CHECK(grbl_enter() == 0);
    CHECK(saw_work_offset && strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[MSG:Restoring defaults]") != NULL);
    coord_system_data_t saved;
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_PARAMETERS, sizeof(saved), true) == NVS_TransferResult_OK);
    NEAR(saved.coord.x, 0); NEAR(saved.coord.y, 0); NEAR(saved.coord.z, 0);
    return EXIT_SUCCESS;
}
