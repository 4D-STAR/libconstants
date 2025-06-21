# Test files for const
test_sources = [
    'constTest.cpp',
]

foreach test_file : test_sources
  exe_name = test_file.split('.')[0]
  message('Building test: ' + exe_name)

  # Create an executable target for each test
  test_exe = executable(
      exe_name,
      test_file,
      dependencies: [gtest_dep, const_dep, gtest_main],
      include_directories: include_directories('../../src/constants/public'),
      link_with: libconst,  # Link the dobj library
      install_rpath: '@loader_path/../../src'  # Ensure runtime library path resolves correctly
  )

  # Add the executable as a test
  test(exe_name, test_exe)
endforeach
