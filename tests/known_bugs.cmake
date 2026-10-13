# Confirmed defects: keep each regression and remove its block when fixed.
# Dates, reproductions, and removal instructions: KNOWN_BUGS.md

if(TEST nuts_bolts.datetime_century_leap)
  set_tests_properties(nuts_bolts.datetime_century_leap PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_ram.close_lifetime)
  set_tests_properties(fs_ram.close_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_embedded.seek_within_file)
  set_tests_properties(fs_embedded.seek_within_file PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST delta.unreachable_cartesian_target_rejected)
  set_tests_properties(delta.unreachable_cartesian_target_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST rtcp_ac.rotary_segment_endpoint)
  set_tests_properties(rtcp_ac.rotary_segment_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.m68_preserves_fractional_output)
  set_tests_properties(gcode.m68_preserves_fractional_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Spindle listing uses the registered slot settings.
# The test follows supported setup and passes normally.
# No known-bug exception is needed.

# MPG commands intentionally allow one outstanding command at a time.
# Covered by stream.mpg_buffered_commands_wait_for_response.
# This is an ordinary passing test of the supported command/response protocol.

if(TEST ngc_params.builtin_modbus_macro_preserves_three_register_results)
  set_tests_properties(ngc_params.builtin_modbus_macro_preserves_three_register_results PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# ngc_flowctrl.named_macro_call_opens_file_and_sets_local_arguments
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

# ngc_flowctrl.named_macro_eof_restores_caller_stream_and_parameter_scope
# Uses a static backend to test EOF restoration independently of file freeing.
# Ordinary passing test; no known-bug exception.

if(TEST ngc_flowctrl.named_macro_return_closes_file_and_restores_caller_scope)
  set_tests_properties(ngc_flowctrl.named_macro_return_closes_file_and_restores_caller_scope PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_return_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_return_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_end_sub_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_end_sub_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_error_preserves_subroutine_callback_lifetime)
  set_tests_properties(ngc_flowctrl.named_macro_error_preserves_subroutine_callback_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Dynamic laser power is not restored after a separate M4 command; verified 2026-10-13 on core 4b128e6.
if(TEST gcode.clockwise_laser_arc_segments_keep_dynamic_power)
  set_tests_properties(gcode.clockwise_laser_arc_segments_keep_dynamic_power PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.counterclockwise_laser_arc_segments_keep_dynamic_power)
  set_tests_properties(gcode.counterclockwise_laser_arc_segments_keep_dynamic_power PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.laser_check_mode_updates_parser_without_driver_output)
  set_tests_properties(gcode.laser_check_mode_updates_parser_without_driver_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.previously_enabled_dynamic_laser_cut_uses_rate_adjusted_power)
  set_tests_properties(gcode.previously_enabled_dynamic_laser_cut_uses_rate_adjusted_power PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST stepper.dynamic_laser_pwm_tracks_acceleration_and_returns_to_zero)
  set_tests_properties(stepper.dynamic_laser_pwm_tracks_acceleration_and_returns_to_zero PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


# Empty tool-table slots lose their tool identity; verified 2026-10-13 on core 4b128e6.
if(TEST tool_table.checksum_failure_returns_zeroed_tool)
  set_tests_properties(tool_table.checksum_failure_returns_zeroed_tool PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST tool_table.g10_l1_persists_tool_offsets_and_radius)
  set_tests_properties(tool_table.g10_l1_persists_tool_offsets_and_radius PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST tool_table.missing_storage_returns_zeroed_tool_with_requested_id)
  set_tests_properties(tool_table.missing_storage_returns_zeroed_tool_with_requested_id PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST tool_table.valid_checksum_with_wrong_tool_id_returns_zeroed_slot)
  set_tests_properties(tool_table.valid_checksum_with_wrong_tool_id_returns_zeroed_slot PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
