# Outstanding allowances only. Keep regression assertions when removing a block.
# Dated evidence and cleanup: KNOWN_BUGS.md; storage policy: TODO.md.

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed directory validation/root-routing defects, Terje fab8d1c (2026-10-22).

if(TEST fs_embedded.hidden_only_directory_has_no_visible_entries)
  set_tests_properties(fs_embedded.hidden_only_directory_has_no_visible_entries PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_embedded.visible_registration_reveals_previously_hidden_mount)
  set_tests_properties(fs_embedded.visible_registration_reveals_previously_hidden_mount PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()






# Observed upload failure; demarcation contract remains pending maintainer review.
if(TEST boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked)
  set_tests_properties(boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()



if(TEST cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses)
  set_tests_properties(cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


if(TEST ngc_params.m72_restores_override_percentages_when_enable_flags_are_unchanged)
  set_tests_properties(ngc_params.m72_restores_override_percentages_when_enable_flags_are_unchanged PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST boot_square.engaged_switches_pull_off_before_independent_motor_homing)
  set_tests_properties(boot_square.engaged_switches_pull_off_before_independent_motor_homing PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST rtcp_ac.rotation_at_tool_center_preserves_requested_rotary_endpoint)
  set_tests_properties(rtcp_ac.rotation_at_tool_center_preserves_requested_rotary_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ngc_flowctrl.named_macro_flow_syntax_error_closes_file_before_status_returns)
  set_tests_properties(ngc_flowctrl.named_macro_flow_syntax_error_closes_file_before_status_returns PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()



if(TEST fs_ram.truncate_pending_upload_discards_old_bytes_before_replacement)
  set_tests_properties(fs_ram.truncate_pending_upload_discards_old_bytes_before_replacement PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ioports.allocation_failure_digital_bank_preserves_counts_and_allows_retry)
  set_tests_properties(ioports.allocation_failure_digital_bank_preserves_counts_and_allows_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ioports.allocation_failure_first_analog_bank_preserves_counts_and_allows_retry)
  set_tests_properties(ioports.allocation_failure_first_analog_bank_preserves_counts_and_allows_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST modbus_rtu.full_async_queue_reports_backpressure_and_preserves_accepted_requests)
  set_tests_properties(modbus_rtu.full_async_queue_reports_backpressure_and_preserves_accepted_requests PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST boot_delta_aux.streamed_auxiliary_move_preserves_delta_joints_and_reaches_a_endpoint)
  set_tests_properties(boot_delta_aux.streamed_auxiliary_move_preserves_delta_joints_and_reaches_a_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


if(TEST system.startup_comment_rejection_preserves_saved_line_and_allows_retry)
  set_tests_properties(system.startup_comment_rejection_preserves_saved_line_and_allows_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
  if(ENABLE_SANITIZERS)
    set_tests_properties(system.startup_comment_rejection_preserves_saved_line_and_allows_retry PROPERTIES LABELS "known_bug;known_crash")
  endif()
endif()

if(TEST ioports.pwm_large_request_clamps_before_minimum_duty_addition_can_wrap)
  include(CheckCSourceCompiles)
  check_c_source_compiles("#include <stdint.h>
#if UINT_FAST16_MAX != 65535
#error This target does not use a 16-bit uint_fast16_t
#endif
int main(void) { return 0; }" HOST_UINT_FAST16_IS_16_BITS)
  if(HOST_UINT_FAST16_IS_16_BITS)
    set_tests_properties(ioports.pwm_large_request_clamps_before_minimum_duty_addition_can_wrap
      PROPERTIES WILL_FAIL TRUE LABELS known_bug)
  endif()
endif()

if(TEST ioports.pwm_frequency_above_timer_clock_reports_no_range_and_allows_valid_retry)
  set_tests_properties(ioports.pwm_frequency_above_timer_clock_reports_no_range_and_allows_valid_retry
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Same-block lathe plane validation uses the old modal plane (2026-10-23).
if(TEST lathe_ngc.roughing_same_block_plane_change_uses_selected_plane_before_dispatch)
  set_tests_properties(lathe_ngc.roughing_same_block_plane_change_uses_selected_plane_before_dispatch
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST lathe_ngc.roughing_same_block_xy_plane_is_rejected_before_plugin_dispatch)
  set_tests_properties(lathe_ngc.roughing_same_block_xy_plane_is_rejected_before_plugin_dispatch
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# A named-file prescan must reject EOF without a matching ENDSUB (2026-10-23).
if(TEST ngc_flowctrl.named_file_without_end_sub_rejects_without_executing_body)
  set_tests_properties(ngc_flowctrl.named_file_without_end_sub_rejects_without_executing_body
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(ENABLE_SANITIZERS AND TEST ngc_flowctrl.continue_to_missing_loop_label_reports_syntax_without_reading_past_stack)
  set_tests_properties(ngc_flowctrl.continue_to_missing_loop_label_reports_syntax_without_reading_past_stack
    PROPERTIES WILL_FAIL TRUE LABELS "known_bug;known_crash")
endif()

# Arc bounding box omits a Y endpoint when no Y extremum is crossed (2026-10-23).
if(TEST motion_control.clockwise_arc_rejects_endpoint_above_y_limit_before_emitting_steps)
  set_tests_properties(motion_control.clockwise_arc_rejects_endpoint_above_y_limit_before_emitting_steps
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
if(TEST motion_control.counterclockwise_arc_rejects_endpoint_below_y_limit_before_emitting_steps)
  set_tests_properties(motion_control.counterclockwise_arc_rejects_endpoint_below_y_limit_before_emitting_steps
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Maintainer full-path-only hidden-file contract,2026-10-23, CORE50f3865.
if(TEST fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir)
  set_tests_properties(fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Mismatched numeric ENDSUB accepts the last registered sub, CORE50f3865.
if(TEST ngc_flowctrl.file_subroutine_with_mismatched_endsub_rejects_before_body_and_restores_sender)
  set_tests_properties(ngc_flowctrl.file_subroutine_with_mismatched_endsub_rejects_before_body_and_restores_sender PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Rejected auxiliary one-step request changes running direction, CORE50f3865.
if(TEST stepper2.rejected_reverse_nudge_preserves_running_finite_move)
  set_tests_properties(stepper2.rejected_reverse_nudge_preserves_running_finite_move PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Error classification reads the stale output after parse failure, CORE50f3865.
if(TEST ngc_expr.unary_name_error_is_preserved_with_nonfinite_output_sentinel)
  set_tests_properties(ngc_expr.unary_name_error_is_preserved_with_nonfinite_output_sentinel PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Synthesized EOF linefeed omits the file line-counter increment, CORE50f3865.
if(TEST stream_file.unterminated_last_command_receives_next_line_number_before_eof)
  set_tests_properties(stream_file.unterminated_last_command_receives_next_line_number_before_eof PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Adding a bank invalidates total count but not cached free count, CORE50f3865.
if(TEST ioports.free_port_counts_refresh_when_expansion_registers_after_discovery_query)
  set_tests_properties(ioports.free_port_counts_refresh_when_expansion_registers_after_discovery_query PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
