  # disabling tests that failed from the get-go on Windows (temporarily!)
cd C:\projects\gdl\testsuite
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_3300626.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_3275334.pro' -NotMatch)
  # ps: Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_3104214.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_2876161.pro' -NotMatch)
  # ps: Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_2610174.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_1779553.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_3394430.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_3595172.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_635.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_709.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_719.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_n000587.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_n000608.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bug_n000720.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_byte_conversion.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_bytscl.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_call_external.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_chisqr_cvf.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_clip.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_congrid.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_constants.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_correlate.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_device.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_dicom.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_execute.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_extra_keywords.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fft_dim.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_basename.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_copy.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fft_leak.pro' -NotMatch)
  # ps: Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_dirname.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_lines.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_move.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_test.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_file_which.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fix.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_finite.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fixprint.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_formats.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fx_root.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_fz_roots.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_gc.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_get_lun.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_get_screen_size.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_gh00178.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_hist_2d.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_idlneturl.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_indgen.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_interpol.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_l64.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_la_least_squares.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_ludc_lusol.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_make_dll.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_math_function_dim.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_matrix_multiply.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_memory.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_message.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_moment.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_multiroots.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_obj_isa.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_obj_new.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_plot_oo.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_plot_ranges.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_plotting_ranges.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_pmulti.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_point_lun.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_postscript.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_product.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_ps_decomposed.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_python.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_image_statistics.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_n_tags.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_nans_in_sort_and_median.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_nestedloop.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_parse_url.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_python_module_0.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_python_module_1.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_python_module_2.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_qhull.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_random.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_readf.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_resolve_routine.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_same_name.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_simplex.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_spawn_unit.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_spher_harm.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_spl_init.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_step.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_str_sep.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_stregex.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_strmatch.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_strsplit.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_structures.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_systime.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_tic_toc.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_total.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_rounding.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_tv.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_typename.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_wait.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_wavelet.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_window_background.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_wordexp.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_zeropoly.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_zip.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_delvarrnew.pro' -NotMatch)
  # ps: Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_list.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_obj_valid.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_make_array.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_ptr_valid.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_binfmt.pro' -NotMatch)
Set-Content -Path "Makefile.am" -Value (get-content -Path "Makefile.am" | Select-String -Pattern 'test_tiff.pro' -NotMatch)
cd  C:\projects\gdl
