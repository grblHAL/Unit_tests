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

if(TEST vfs_integration.formatting_current_drive_resets_removed_subdirectory_to_drive_root)
  set_tests_properties(vfs_integration.formatting_current_drive_resets_removed_subdirectory_to_drive_root PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# MPG's enum lies outside the guard protecting its pull-up initialization.
foreach(name ioports.loaded_first_mpg_input_receives_pullup_without_neighbor_state
    ioports.loaded_mpg_input_does_not_inherit_neighbor_pulldown)
  if(TEST ${name})
    set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE LABELS known_bug)
  endif()
endforeach()

if(TEST ngc_flowctrl.macro_while_expression_allocation_failure_returns_to_sender_and_retries)
  set_tests_properties(ngc_flowctrl.macro_while_expression_allocation_failure_returns_to_sender_and_retries PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.pre_execute_rejection_releases_core_message_and_preserves_queued_motion)
  set_tests_properties(lathe_ngc.pre_execute_rejection_releases_core_message_and_preserves_queued_motion PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST lathe_ngc.parser_rejection_releases_message_and_preserves_queued_motion)
  set_tests_properties(lathe_ngc.parser_rejection_releases_message_and_preserves_queued_motion PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Observed upload failure; demarcation contract remains pending maintainer review.
if(TEST boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked)
  set_tests_properties(boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.relative_unlink_path_allocation_failure_preserves_other_directory_and_retries)
  set_tests_properties(vfs.relative_unlink_path_allocation_failure_preserves_other_directory_and_retries PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST gcode.trailing_comment_does_not_clear_material_validation_error)
  set_tests_properties(gcode.trailing_comment_does_not_clear_material_validation_error PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses)
  set_tests_properties(cutter_comp.direct_modal_restore_preserves_disabled_mode_when_extension_refuses PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST spindle_sync.unsupported_rigid_tapping_preserves_position_and_next_supported_sync_move)
  set_tests_properties(spindle_sync.unsupported_rigid_tapping_preserves_position_and_next_supported_sync_move PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()
