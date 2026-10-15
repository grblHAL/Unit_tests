#include "support/settings_metadata_report_host.h"
static char help_output[32768];
static void write_help(const char *text)
{
    CHECK(strlen(help_output) + strlen(text) < sizeof(help_output));
    strcat(help_output, text);
}
int main(void)
{
    prepare_metadata_report();
    hal.stream.write = write_help;
    char topic[] = "settings";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strstr(help_output, "Visible first") != NULL);
    CHECK(strstr(help_output, "Other group") != NULL);
    CHECK(strstr(help_output, "Hidden setting") == NULL);
    CHECK(strstr(help_output, "Unavailable setting") == NULL);
    return EXIT_SUCCESS;
}
