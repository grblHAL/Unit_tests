#include "support/ram_macro_protocol_host.h"
#include "fs_embedded.h"

#define NAME_PART "fixture_xxxxxxxxxxxx"
#define MACRO_NAME NAME_PART NAME_PART NAME_PART NAME_PART
#define MACRO_BODY "O<" MACRO_NAME ">SUB\n#100=#1\nG999\n#100=88\nO<" MACRO_NAME ">ENDSUB\n"
static const embedded_file_t asset = {.name = MACRO_NAME ".macro",
    .data = MACRO_BODY, .size = sizeof(MACRO_BODY) - 1};
static const embedded_file_t *assets[] = {&asset, NULL};
static void mount_macro(void) { CHECK(fs_embedded_mount(assets)); }

int main(void)
{
    CHECK(NGC_MAX_PARAM_LENGTH == 80 && strlen(MACRO_NAME) == NGC_MAX_PARAM_LENGTH);
    ram_prepare_assets = mount_macro;
    ram_expected_root_status = Status_GcodeUnsupportedCommand;
    run_ram_root_protocol("#1=99\n#101=0\nO<" MACRO_NAME ">CALL[12]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(1), 99);
    CHECK(strstr(engine_output, "in named sub ") != NULL);
    CHECK(strstr(engine_output, "*.macro") != NULL);
    CHECK(strstr(engine_output, MACRO_NAME ".macro") == NULL);
    return EXIT_SUCCESS;
}
