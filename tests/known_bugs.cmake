# Outstanding allowances only. Keep regression assertions when removing a block.
# Dated evidence and cleanup: KNOWN_BUGS.md; storage policy: TODO.md.

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Observed upload failure; demarcation contract remains pending maintainer review.
if(TEST boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked)
  set_tests_properties(boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses)
  set_tests_properties(cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST boot_square.engaged_switches_pull_off_before_independent_motor_homing)
  set_tests_properties(boot_square.engaged_switches_pull_off_before_independent_motor_homing PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST rtcp_ac.rotation_at_tool_center_preserves_requested_rotary_endpoint)
  set_tests_properties(rtcp_ac.rotation_at_tool_center_preserves_requested_rotary_endpoint PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ioports.allocation_failure_digital_bank_preserves_counts_and_allows_retry)
  set_tests_properties(ioports.allocation_failure_digital_bank_preserves_counts_and_allows_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST ioports.allocation_failure_first_analog_bank_preserves_counts_and_allows_retry)
  set_tests_properties(ioports.allocation_failure_first_analog_bank_preserves_counts_and_allows_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
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

# Maintainer full-path-only hidden-file contract,2026-10-23, CORE50f3865.
if(TEST fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir)
  set_tests_properties(fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Accepted combined M3/M48 broadcast sets disable bits instead of clearing them.
if(TEST multi_spindle.broadcast_spindle_start_with_m48_restores_both_speed_overrides)
  set_tests_properties(multi_spindle.broadcast_spindle_start_with_m48_restores_both_speed_overrides PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Failed filename growth returns the previous successful path, CORE2e165a1.
if(TEST vfs.locate_allocation_failure_does_not_return_previous_job_and_allows_retry)
  set_tests_properties(vfs.locate_allocation_failure_does_not_return_previous_job_and_allows_retry
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed on CORE2e165a1, 2026-10-23: failed file allocation retains passthru.
if(TEST fs_device.open_allocation_failure_releases_device_for_retry)
  set_tests_properties(fs_device.open_allocation_failure_releases_device_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: null console is confused with no saved stream.
if(TEST stream.mpg_disable_after_network_disconnect_restores_null_console)
  set_tests_properties(stream.mpg_disable_after_network_disconnect_restores_null_console
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Exact recovering UBSan in supported 32-channel bank registration; assertions pass.
if(ENABLE_SANITIZERS AND TEST ioports_32.full_bank_registers_p31_and_routes_highest_channels)
  set_tests_properties(ioports_32.full_bank_registers_p31_and_routes_highest_channels
    PROPERTIES LABELS known_sanitizer_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: deferred tool-zero G43 retains the previous offsets.
if(TEST gcode.m6_unloading_tool_with_g43_clears_previous_offset_after_sender_ack)
  set_tests_properties(gcode.m6_unloading_tool_with_g43_clears_previous_offset_after_sender_ack
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: blocking CRC failure reports NoException.
if(TEST modbus_rtu.blocking_crc_error_reports_crc_code_and_allows_next_request)
  set_tests_properties(modbus_rtu.blocking_crc_error_reports_crc_code_and_allows_next_request
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: manual A homing rewrites stationary delta XYZ coordinates.
if(TEST boot_delta_aux.manual_auxiliary_homing_preserves_delta_joint_coordinates)
  set_tests_properties(boot_delta_aux.manual_auxiliary_homing_preserves_delta_joint_coordinates
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Same public manual-reference sequence also rejects a legal in-range A retry.
if(TEST boot_delta_aux.manually_homed_auxiliary_axis_rejects_outside_jog_and_allows_inside_retry)
  set_tests_properties(boot_delta_aux.manually_homed_auxiliary_axis_rejects_outside_jog_and_allows_inside_retry
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: delta forwards motor-coordinate flag to Cartesian auxiliary checker.
if(TEST boot_delta_aux.valid_cartesian_cut_with_stationary_homed_auxiliary_axis_does_not_raise_soft_limit)
  set_tests_properties(boot_delta_aux.valid_cartesian_cut_with_stationary_homed_auxiliary_axis_does_not_raise_soft_limit
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: utime path allocation loses ENOMEM.
if(TEST vfs.utime_path_allocation_failure_preserves_errno_skips_backend_and_allows_retry)
  set_tests_properties(vfs.utime_path_allocation_failure_preserves_errno_skips_backend_and_allows_retry
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: accepted async follow-up from blocking reply is discarded.
if(TEST modbus_rtu.blocking_reply_followup_is_transmitted_if_send_reports_acceptance)
  set_tests_properties(modbus_rtu.blocking_reply_followup_is_transmitted_if_send_reports_acceptance
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed CORE2e165a1, 2026-10-24: decoder mistakes valid server address high bit for exception.
if(TEST modbus_rtu.high_bit_server_address_delivers_register_reply_and_preserves_next_request)
  set_tests_properties(modbus_rtu.high_bit_server_address_delivers_register_reply_and_preserves_next_request
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed COREb01f481, 2026-10-24: failed embedded mount changes unrelated root visibility.
if(TEST fs_embedded.allocation_failure_first_mount_preserves_root_mode_and_allows_asset_retry)
  set_tests_properties(fs_embedded.allocation_failure_first_mount_preserves_root_mode_and_allows_asset_retry
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed COREb01f481 on hosted Linux Clang: exact macro argument table bounds fault.
if(HOST_TAPPING_KNOWN_CRASH)
  foreach(tapping_case IN LISTS HOST_TAPPING_CRASH_CASES)
    if(TEST ${tapping_case})
      set_tests_properties(${tapping_case} PROPERTIES WILL_FAIL TRUE LABELS "known_bug;known_crash")
    endif()
  endforeach()
endif()

# Confirmed COREb01f481, 2026-10-24: 29-argument CALL omits initialization of inherited local30.
if(TEST ngc_flowctrl.call_with_twenty_nine_arguments_inherits_last_local_and_restores_caller)
  set_tests_properties(ngc_flowctrl.call_with_twenty_nine_arguments_inherits_last_local_and_restores_caller
    PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
