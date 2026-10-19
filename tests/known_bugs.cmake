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

# Restored archived regression; still reproduced on Terje e65020a (2026-10-13).
if(TEST gcode.file_percent_marker_after_unmarked_start_is_rejected)
  set_tests_properties(gcode.file_percent_marker_after_unmarked_start_is_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Deferred storage failure policy: tests/TODO.md#storage-write-failure-policy.
# Retain current exceptions until the maintainer chooses/implements the contract.

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

# Failed cwd growth must release the old heap allocation before root fallback.
if(TEST vfs.current_directory_reallocation_failure_falls_back_to_root)
  set_tests_properties(vfs.current_directory_reallocation_failure_falls_back_to_root
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug")
endif()

# Live and loaded configuration must agree for the same pullup-disable setting.
if(TEST ioports_pullup.pullup_disable_live_and_loaded_configuration_agree)
  set_tests_properties(ioports_pullup.pullup_disable_live_and_loaded_configuration_agree
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug")
endif()

# G83 cancellation during synchronized drilling must preserve actual stopped Z.
if(TEST motion_control.sender_stop_during_peck_drill_synchronization_preserves_restart_position)
  set_tests_properties(motion_control.sender_stop_during_peck_drill_synchronization_preserves_restart_position
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Settings-list allocator fallback must preserve visibility and requested scope.
if(TEST report.all_settings_sort_allocation_failure_preserves_hidden_and_unavailable_filter)
  set_tests_properties(report.all_settings_sort_allocation_failure_preserves_hidden_and_unavailable_filter
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST report.all_settings_sort_allocation_failure_preserves_legacy_only_selection)
  set_tests_properties(report.all_settings_sort_allocation_failure_preserves_legacy_only_selection
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Door interruption after manual completion must not lose the pending parser tool.
if(TEST tool_change.open_door_at_manual_completion_queues_safety_door_before_motion)
  set_tests_properties(tool_change.open_door_at_manual_completion_queues_safety_door_before_motion
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Reset during manual tool-positioning must not select the uncompleted tool.
if(TEST boot.sender_reset_during_tool_positioning_restarts_without_selecting_unfitted_tool)
  set_tests_properties(boot.sender_reset_during_tool_positioning_restarts_without_selecting_unfitted_tool
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Segmented jog cancellation must retain the actual stopped parser position.
if(TEST boot_delta.sender_jog_cancel_stops_segment_refill_and_syncs_cartesian_position)
  set_tests_properties(boot_delta.sender_jog_cancel_stops_segment_refill_and_syncs_cartesian_position
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Valid uint32 values must not be rejected based solely on their last digit.
if(TEST settings.registered_plugin_counter_accepts_valid_ten_digit_value_ending_in_nine)
  set_tests_properties(settings.registered_plugin_counter_accepts_valid_ten_digit_value_ending_in_nine
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST nuts_bolts.read_uint_valid_ten_digit_values_ending_above_five)
  set_tests_properties(nuts_bolts.read_uint_valid_ten_digit_values_ending_above_five
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Nested CRLF callers must retain physical line numbers after asynchronous G65 return.
if(TEST ngc_params.nested_crlf_ram_g65_files_preserve_physical_line_numbers)
  set_tests_properties(ngc_params.nested_crlf_ram_g65_files_preserve_physical_line_numbers
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Each appended embedded-file list must be searched from its first entry.
if(TEST fs_embedded.later_registered_file_can_be_opened_after_searching_first_list)
  set_tests_properties(fs_embedded.later_registered_file_can_be_opened_after_searching_first_list
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Correct output assertions pass; only sanitizer builds must reproduce this diagnostic.
# Remove this label AND its scoped manifest entry when the signed negation is fixed.
if(ENABLE_SANITIZERS AND TEST stream_json.minimum_signed_integer_emits_full_decimal_value)
  set_tests_properties(stream_json.minimum_signed_integer_emits_full_decimal_value
    PROPERTIES LABELS known_sanitizer_bug)
endif()

# Optional return expressions must use callee locals before the scope is unwound.
if(TEST ngc_flowctrl.embedded_named_recursive_return_preserves_outer_return_value)
  set_tests_properties(ngc_flowctrl.embedded_named_recursive_return_preserves_outer_return_value
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST ngc_flowctrl.embedded_named_recursive_endsub_closes_each_real_file_handle)
  set_tests_properties(ngc_flowctrl.embedded_named_recursive_endsub_closes_each_real_file_handle
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# A running normal spindle must apply override changes while feed hold remains active.
if(TEST state_machine.held_running_spindle_overrides_update_output_without_axis_motion)
  set_tests_properties(state_machine.held_running_spindle_overrides_update_output_without_axis_motion
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
