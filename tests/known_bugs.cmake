# Outstanding allowances only. Keep regression assertions when removing a block.
# Dated evidence and cleanup: KNOWN_BUGS.md; storage policy: TODO.md.

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed directory validation/root-routing defects, Terje fab8d1c (2026-10-22).








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



# A named-file prescan must reject EOF without a matching ENDSUB (2026-10-23).


# Arc bounding box omits a Y endpoint when no Y extremum is crossed (2026-10-23).

# Maintainer full-path-only hidden-file contract,2026-10-23, CORE50f3865.
if(TEST fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir)
  set_tests_properties(fs_embedded.hidden_file_in_visible_mount_requires_full_path_after_chdir PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Mismatched numeric ENDSUB accepts the last registered sub, CORE50f3865.



# Synthesized EOF linefeed omits the file line-counter increment, CORE50f3865.

# Adding a bank invalidates total count but not cached free count, CORE50f3865.

# Failed rigid-tapping synchronization enters the macro fallback, CORE50f3865.
if(TEST spindle_sync.stopped_spindle_rejects_rigid_tapping_without_calling_macro_fallback)
  set_tests_properties(spindle_sync.stopped_spindle_rejects_rigid_tapping_without_calling_macro_fallback PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Accepted combined M3/M48 broadcast sets disable bits instead of clearing them.
if(TEST multi_spindle.broadcast_spindle_start_with_m48_restores_both_speed_overrides)
  set_tests_properties(multi_spindle.broadcast_spindle_start_with_m48_restores_both_speed_overrides PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Ordinary nonzero RAM-file shrink loses its allocation base, CORE51b58594.
if(TEST fs_ram.truncate_committed_file_to_nonzero_length_preserves_prefix)
  set_tests_properties(fs_ram.truncate_committed_file_to_nonzero_length_preserves_prefix PROPERTIES WILL_FAIL TRUE LABELS known_bug)
  if(ENABLE_SANITIZERS)
    set_tests_properties(fs_ram.truncate_committed_file_to_nonzero_length_preserves_prefix PROPERTIES LABELS "known_bug;known_crash")
  endif()
endif()

if(TEST fs_ram.truncate_pending_upload_to_shorter_nonzero_length_preserves_prefix)
  set_tests_properties(fs_ram.truncate_pending_upload_to_shorter_nonzero_length_preserves_prefix PROPERTIES WILL_FAIL TRUE LABELS known_bug)
  if(ENABLE_SANITIZERS)
    set_tests_properties(fs_ram.truncate_pending_upload_to_shorter_nonzero_length_preserves_prefix PROPERTIES LABELS "known_bug;known_crash")
  endif()
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
