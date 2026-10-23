#include "support/description_metadata_host.h"

int main(void)
{
    static const setting_descr_t descriptions[] = {
        {.id = (setting_id_t)1001, .description = "First\\nSecond\\nThird\\n"}
    };
    description_details.descriptions = descriptions;
    prepare_description_metadata();
    report_human_metadata();
    const char *text = strstr(engine_output, "First" ASCII_EOL "Second" ASCII_EOL "Third");
    CHECK(text != NULL);
    CHECK(strstr(engine_output, "\\n") == NULL);
    CHECK(strstr(text + 1, "First") == NULL);
    CHECK(strstr(text, "ThirdThird") == NULL);
    CHECK(human_metadata_value == 0);
    return EXIT_SUCCESS;
}
