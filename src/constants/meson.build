# Define the library
const_sources = files(
  'lib/const.cpp',
)


# Define the libconst library so it can be linked against by other parts of the build system
fourdst_component_libdir = get_option('lib_install_dir') != '' ? get_option('lib_install_dir') : get_option('libdir')
libconst = library('const',
    const_sources, 
    include_directories: include_directories('include'),
    cpp_args: ['-fvisibility=default'],
    dependencies: [const_data_dep],
    install : true,
    install_dir: fourdst_component_libdir)

const_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: libconst,
)

# Make headers accessible
const_headers = files(
  'include/fourdst/constants/const.h'
)
install_headers(const_headers, subdir : 'fourdst/constants')
