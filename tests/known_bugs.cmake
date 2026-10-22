# Outstanding allowances only. Keep regression assertions when removing a block.
# Dated evidence and cleanup: KNOWN_BUGS.md; storage policy: TODO.md.

if(TEST nvs_buffer.failed_version_only_write_remains_pending_for_retry)
  set_tests_properties(nvs_buffer.failed_version_only_write_remains_pending_for_retry PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.getcwd_without_backend_handler_preserves_mount_prefix_once)
  set_tests_properties(vfs.getcwd_without_backend_handler_preserves_mount_prefix_once PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

# Confirmed directory validation/root-routing defects, Terje fab8d1c (2026-10-22).
if(TEST fs_embedded.change_directory_enables_relative_reads_and_rejects_subdirectory)
  set_tests_properties(fs_embedded.change_directory_enables_relative_reads_and_rejects_subdirectory PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_embedded.hidden_only_directory_has_no_visible_entries)
  set_tests_properties(fs_embedded.hidden_only_directory_has_no_visible_entries PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_embedded.visible_registration_reveals_previously_hidden_mount)
  set_tests_properties(fs_embedded.visible_registration_reveals_previously_hidden_mount PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST fs_ram.flat_filesystem_rejects_directory_mutations)
  set_tests_properties(fs_ram.flat_filesystem_rejects_directory_mutations PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.chdir_without_backend_handler_rejects_regular_file)
  set_tests_properties(vfs.chdir_without_backend_handler_rejects_regular_file PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.current_directory_growth_preserves_relative_path_resolution)
  set_tests_properties(vfs.current_directory_growth_preserves_relative_path_resolution PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs.long_current_directory_allocates_and_resolves_relative_stat)
  set_tests_properties(vfs.long_current_directory_allocates_and_resolves_relative_stat PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()

if(TEST vfs_integration.formatting_current_drive_resets_removed_subdirectory_to_drive_root)
  set_tests_properties(vfs_integration.formatting_current_drive_resets_removed_subdirectory_to_drive_root PROPERTIES WILL_FAIL TRUE LABELS known_bug)
endif()


# Fatal diagnostics are matched by exact test/source/frame in known_crash.py.
if(ENABLE_SANITIZERS)
  foreach(name vfs.repeated_chdir_without_getcwd_handler_preserves_relative_resolution
      grbllib.interrupt_cancelling_due_task_before_masking_preserves_later_work)
    if(TEST ${name})
      set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE LABELS "known_bug;known_crash")
    endif()
  endforeach()
endif()
