# Define the library
const_sources = files(
  'lib/const.cpp',
)


samedir_rpath = host_machine.system() == 'darwin' ? '@loader_path' : '$ORIGIN'

libconst = library('const',
    const_sources,
    include_directories: include_directories('include'),
    cpp_args: ['-fvisibility=default'],
    dependencies: [const_data_dep],
    install : true,
    install_dir: constants_libdir,
    install_rpath: samedir_rpath,
    build_rpath: samedir_rpath
)

const_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: libconst,
)

# Make headers accessible
const_headers = files(
  'include/fourdst/constants/const.h'
)

if get_option('build_python')
    install_data(const_headers, install_dir: constants_header_install_dir)
else
    install_headers(const_headers, install_dir: constants_header_install_dir)
endif
