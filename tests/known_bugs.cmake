# Outstanding allowances only. Keep regression assertions when removing a block.
# Dated evidence and cleanup: KNOWN_BUGS.md; storage policy: TODO.md.

if(TEST gcode.m68_preserves_fractional_output)
  set_tests_properties(gcode.m68_preserves_fractional_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.file_percent_marker_after_unmarked_start_is_rejected)
  set_tests_properties(gcode.file_percent_marker_after_unmarked_start_is_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.parent_path_crossing_mount_passes_target_local_filename)
  set_tests_properties(vfs.parent_path_crossing_mount_passes_target_local_filename PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.current_directory_reallocation_failure_falls_back_to_root)
  set_tests_properties(vfs.current_directory_reallocation_failure_falls_back_to_root
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug")
endif()


# Explicit G65 calls must retain required-P/default-repeat validation while G66 is armed.
if(TEST ngc_params.g65_default_repeat_with_armed_g66_dispatches_one_iteration)
  set_tests_properties(ngc_params.g65_default_repeat_with_armed_g66_dispatches_one_iteration PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST ngc_params.g65_missing_macro_number_with_armed_g66_rejects_before_callback)
  set_tests_properties(ngc_params.g65_missing_macro_number_with_armed_g66_rejects_before_callback PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
