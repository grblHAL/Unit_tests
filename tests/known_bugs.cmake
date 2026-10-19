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


# Explicit G65 calls must retain required-P/default-repeat validation while G66 is armed.
if(TEST ngc_params.g65_default_repeat_with_armed_g66_dispatches_one_iteration)
  set_tests_properties(ngc_params.g65_default_repeat_with_armed_g66_dispatches_one_iteration PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST ngc_params.g65_missing_macro_number_with_armed_g66_rejects_before_callback)
  set_tests_properties(ngc_params.g65_missing_macro_number_with_armed_g66_rejects_before_callback PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
