#include "support/ram_macro_protocol_host.h"
#include "fs_embedded.h"
static const embedded_file_t unterminated = {.name = "fixture.macro",
    .size = sizeof("O<fixture>SUB\n#100=99\n(MSG,Must not execute)\n") - 1,
    .data = "O<fixture>SUB\n#100=99\n(MSG,Must not execute)\n"};
static const embedded_file_t *assets[] = {&unterminated, NULL};
static unsigned rejected_eofs;
static status_code_t observe_invalid_eof(vfs_file_t *file, status_code_t status)
{
    if(file != ram_macro_files[0]) {
        rejected_eofs++;
        NEAR(ram_flow_parameter(100), 0);
        CHECK(strstr(engine_output, "Must not execute") == NULL);
    }
    return status;
}
static void install_invalid_file(void)
{
    fs_embedded_mount(assets);
    grbl.on_file_end = observe_invalid_eof;
}
int main(void)
{
    ram_prepare_assets = install_invalid_file;
    ram_expected_root_status = Status_FlowControlSyntaxError;
    run_ram_root_protocol("#100=0\n#101=0\nO<fixture>CALL\n#101=7\n");
    CHECK(rejected_eofs == 1);
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 0);
    CHECK(strstr(engine_output, "Must not execute") == NULL);
    return EXIT_SUCCESS;
}
