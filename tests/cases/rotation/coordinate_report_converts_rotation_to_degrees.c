#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report(); coord_system_data_t offset={.coord={.x=1,.y=2,.z=3},.rotation=90*RADDEG};
    settings_write_coord_data(CoordinateSystem_G55,&offset); report_ngc_parameters();
    CHECK(strstr(engine_output,"[G55:1.000,2.000,3.000:90.00]" ASCII_EOL)!=NULL);
    return EXIT_SUCCESS;
}
