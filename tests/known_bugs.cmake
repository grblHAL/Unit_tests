# Confirmed defects: keep each regression and remove its block when fixed.
# Dates, reproductions, and removal instructions: KNOWN_BUGS.md

if(TEST gcode.m68_preserves_fractional_output)
  set_tests_properties(gcode.m68_preserves_fractional_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Spindle listing uses the registered slot settings.
# The test follows supported setup and passes normally.
# No known-bug exception is needed.

# MPG commands intentionally allow one outstanding command at a time.
# Covered by stream.mpg_buffered_commands_wait_for_response.
# This is an ordinary passing test of the supported command/response protocol.

# ngc_flowctrl.named_macro_call_opens_file_and_sets_local_arguments
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

# ngc_flowctrl.named_macro_eof_restores_caller_stream_and_parameter_scope
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

# M72 leaves parser feed override control disabled; verified 2026-10-13 on e65020a.
if(TEST ngc_params.m72_restores_feed_and_rapid_overrides_after_m50_disable)
  set_tests_properties(ngc_params.m72_restores_feed_and_rapid_overrides_after_m50_disable PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Restored archived regression; still reproduced on Terje e65020a (2026-10-13).
if(TEST gcode.file_percent_marker_after_unmarked_start_is_rejected)
  set_tests_properties(gcode.file_percent_marker_after_unmarked_start_is_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


# Named motion parameter exposes internal enums; verified 2026-10-13 on e65020a.
if(TEST lathe_ngc.named_motion_mode_reports_g71)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g71 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.named_motion_mode_reports_g71_1)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g71_1 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.named_motion_mode_reports_g72)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g72 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_2)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_2 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_3)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_3 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_4)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_4 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_g38_5)
  set_tests_properties(ngc_params.named_motion_mode_reports_g38_5 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_reports_quadratic_spline_code)
  set_tests_properties(ngc_params.named_motion_mode_reports_quadratic_spline_code PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


# Motion enum refactor regressions verified 2026-10-14 on Terje 50055a2.
if(TEST gcode.quadratic_nonzero_j_accepted)
  set_tests_properties(gcode.quadratic_nonzero_j_accepted PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST motion_control.quadratic_spline_executes)
  set_tests_properties(motion_control.quadratic_spline_executes PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.finishing_cycle_passes_default_arguments_to_plugin)
  set_tests_properties(lathe_ngc.finishing_cycle_passes_default_arguments_to_plugin PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.finishing_cycle_passes_explicit_distances_and_pass_count)
  set_tests_properties(lathe_ngc.finishing_cycle_passes_explicit_distances_and_pass_count PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.finishing_cycle_requires_subroutine_number)
  set_tests_properties(lathe_ngc.finishing_cycle_requires_subroutine_number PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.finishing_cycle_requires_zx_plane)
  set_tests_properties(lathe_ngc.finishing_cycle_requires_zx_plane PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.finishing_modal_report_uses_g70)
  set_tests_properties(lathe_ngc.finishing_modal_report_uses_g70 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.named_motion_mode_reports_g70)
  set_tests_properties(lathe_ngc.named_motion_mode_reports_g70 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_motion_mode_tracks_g0_g1_and_g80)
  set_tests_properties(ngc_params.named_motion_mode_tracks_g0_g1_and_g80 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Failed EEPROM sync drops pending startup/version writes; verified 2026-10-14.
if(TEST nvs_buffer.startup_slot_0_failed_sync_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.startup_slot_0_failed_sync_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nvs_buffer.startup_slot_1_failed_sync_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.startup_slot_1_failed_sync_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# VFS current-directory and cross-mount path defects; verified 2026-10-14.
if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.parent_path_crossing_mount_passes_target_local_filename)
  set_tests_properties(vfs.parent_path_crossing_mount_passes_target_local_filename PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Long filename lookup reallocates static storage on Terje 50055a2.
if(TEST vfs.locate_long_filename_returns_mounted_file_path)
  set_tests_properties(vfs.locate_long_filename_returns_mounted_file_path PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Failed mount allocation incorrectly reports success and emits a mounted event.
if(TEST vfs.mount_allocation_failure_reports_failure_without_notification)
  set_tests_properties(vfs.mount_allocation_failure_reports_failure_without_notification PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Root getcwd rejects a correctly sized two-byte buffer on Terje 50055a2.
if(TEST vfs.root_current_directory_fits_exact_two_byte_buffer)
  set_tests_properties(vfs.root_current_directory_fits_exact_two_byte_buffer PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
