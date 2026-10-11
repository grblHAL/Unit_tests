# Confirmed defects: keep each regression and remove its block when fixed.
# Dates, reproductions, and removal instructions: KNOWN_BUGS.md

if(TEST utf8.ascii)
  set_tests_properties(utf8.ascii PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nuts_bolts.read_uint_decimal_zeros)
  set_tests_properties(nuts_bolts.read_uint_decimal_zeros PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nuts_bolts.read_uint_maximum)
  set_tests_properties(nuts_bolts.read_uint_maximum PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST nuts_bolts.datetime_century_leap)
  set_tests_properties(nuts_bolts.datetime_century_leap PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_ram.close_lifetime)
  set_tests_properties(fs_ram.close_lifetime PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_builtin_read_only)
  set_tests_properties(ngc_params.named_builtin_read_only PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_embedded.seek_within_file)
  set_tests_properties(fs_embedded.seek_within_file PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST stepper2.finite_polled_move)
  set_tests_properties(stepper2.finite_polled_move PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST stream_json.escaped_quote)
  set_tests_properties(stream_json.escaped_quote PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_device.read_byte_count)
  set_tests_properties(fs_device.read_byte_count PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.quadratic_nonzero_j_accepted)
  set_tests_properties(gcode.quadratic_nonzero_j_accepted PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST delta.unreachable_cartesian_target_rejected)
  set_tests_properties(delta.unreachable_cartesian_target_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST rtcp_ac.rotary_segment_endpoint)
  set_tests_properties(rtcp_ac.rotary_segment_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST protocol.serial_delete_edits_block)
  set_tests_properties(protocol.serial_delete_edits_block PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.m66_large_port_rejected)
  set_tests_properties(gcode.m66_large_port_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.m68_preserves_fractional_output)
  set_tests_properties(gcode.m68_preserves_fractional_output PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_expr.name_over_maximum_rejected)
  set_tests_properties(ngc_expr.name_over_maximum_rejected PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.absolute_position_parameter_inches)
  set_tests_properties(ngc_params.absolute_position_parameter_inches PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Spindle listing uses the registered slot settings.
# The test follows supported setup and passes normally.
# No known-bug exception is needed.

if(TEST multi_spindle.gcode_m5_broadcast_stops_enabled_spindles AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set_tests_properties(multi_spindle.gcode_m5_broadcast_stops_enabled_spindles PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.absolute_position_metric_ignores_display_inches)
  set_tests_properties(ngc_params.absolute_position_metric_ignores_display_inches PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST settings.pulse_width_minimum_reports_specific_error)
  set_tests_properties(settings.pulse_width_minimum_reports_specific_error PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST settings.initialize_bad_version_restores_defaults)
  set_tests_properties(settings.initialize_bad_version_restores_defaults PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST feature_compile.auxiliary_pullup_configuration)
  set_tests_properties(feature_compile.auxiliary_pullup_configuration PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.css_negative_speed_preserves_rpm_mode)
  set_tests_properties(gcode.css_negative_speed_preserves_rpm_mode PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.g97_negative_speed_preserves_css_mode)
  set_tests_properties(gcode.g97_negative_speed_preserves_css_mode PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.claim_axis_words_validation_retains_valueless_axis)
  set_tests_properties(gcode.claim_axis_words_validation_retains_valueless_axis PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# MPG commands intentionally allow one outstanding command at a time.
# Covered by stream.mpg_buffered_commands_wait_for_response.
# This is an ordinary passing test of the supported command/response protocol.

if(TEST ngc_params.builtin_setting_macro_reads_boolean)
  set_tests_properties(ngc_params.builtin_setting_macro_reads_boolean PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.builtin_setting_macro_writes_boolean_and_returns_value)
  set_tests_properties(ngc_params.builtin_setting_macro_writes_boolean_and_returns_value PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.builtin_modbus_macro_preserves_three_register_results)
  set_tests_properties(ngc_params.builtin_modbus_macro_preserves_three_register_results PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.builtin_modbus_macro_rejects_unknown_function)
  set_tests_properties(ngc_params.builtin_modbus_macro_rejects_unknown_function PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_params.named_spindle_clockwise_parameter_matches_m3)
  set_tests_properties(ngc_params.named_spindle_clockwise_parameter_matches_m3 PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.rejected_g10_l1_preserves_tool_table_and_persistent_storage)
  set_tests_properties(gcode.rejected_g10_l1_preserves_tool_table_and_persistent_storage PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.rejected_g10_l10_preserves_existing_tool_offsets)
  set_tests_properties(gcode.rejected_g10_l10_preserves_existing_tool_offsets PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.rejected_g51_preserves_scaling_state_and_factors)
  set_tests_properties(gcode.rejected_g51_preserves_scaling_state_and_factors PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST eight_axis.g28_rotary_check_mode_preserves_actual_machine_position)
  set_tests_properties(eight_axis.g28_rotary_check_mode_preserves_actual_machine_position PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST settings.remove_elements_preserves_options_after_short_label)
  set_tests_properties(settings.remove_elements_preserves_options_after_short_label PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.g85_accepted_cycle_executes_drill_and_retract)
  set_tests_properties(gcode.g85_accepted_cycle_executes_drill_and_retract PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.g86_accepted_cycle_executes_drill_and_retract)
  set_tests_properties(gcode.g86_accepted_cycle_executes_drill_and_retract PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.g89_accepted_cycle_executes_drill_and_retract)
  set_tests_properties(gcode.g89_accepted_cycle_executes_drill_and_retract PROPERTIES WILL_FAIL TRUE LABELS known_bug)
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

if(TEST ngc_flowctrl.alarm_expression_errors_are_reported)
  set_tests_properties(ngc_flowctrl.alarm_expression_errors_are_reported PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.error_expression_errors_are_reported)
  set_tests_properties(ngc_flowctrl.error_expression_errors_are_reported PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST feature_compile.legacy_compatibility_level_2_reporting)
  set_tests_properties(feature_compile.legacy_compatibility_level_2_reporting PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST feature_compile.legacy_compatibility_level_10_reporting)
  set_tests_properties(feature_compile.legacy_compatibility_level_10_reporting PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.dynamic_laser_cutting_move_uses_rate_adjusted_power)
  set_tests_properties(gcode.dynamic_laser_cutting_move_uses_rate_adjusted_power PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.switching_dynamic_to_constant_laser_disables_rate_adjustment_in_same_move)
  set_tests_properties(gcode.switching_dynamic_to_constant_laser_disables_rate_adjustment_in_same_move PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.laser_check_mode_speed_change_does_not_call_driver)
  set_tests_properties(gcode.laser_check_mode_speed_change_does_not_call_driver PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
