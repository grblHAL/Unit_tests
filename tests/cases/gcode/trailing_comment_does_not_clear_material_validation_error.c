#include "support/queued_motion_rejection_host.h"
static unsigned rejected_comments;
static status_code_t validate_material(char *text)
{
    if(strcmp(text, "Material selection") == 0) {
        rejected_comments++;
        return Status_UserException;
    }
    CHECK(strcmp(text, "Cut contour") == 0);
    return Status_OK;
}
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    grbl.on_gcode_comment = validate_material;
    check_rejected_block_preserves_queued_motion(
        "G20G91G1X2F50(Material selection)(Cut contour)", Status_UserException);
    CHECK(rejected_comments == 1);
    return EXIT_SUCCESS;
}
