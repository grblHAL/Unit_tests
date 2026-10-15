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

# Two enabled PWM spindles must retain independent cached ramp speeds.
if(TEST multi_spindle.primary_pwm_stop_after_secondary_start_never_increases_primary_output)
  set_tests_properties(multi_spindle.primary_pwm_stop_after_secondary_start_never_increases_primary_output
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug")
endif()

# Legacy boolean enable setting must read back the value accepted from the sender.
if(TEST boot_compat_10.legacy_enable_setting_round_trips_through_sender_query)
  set_tests_properties(boot_compat_10.legacy_enable_setting_round_trips_through_sender_query
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug")
endif()
