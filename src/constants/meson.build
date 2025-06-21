# Define the library
const_sources = files(
  'private/const.cpp',
)

const_headers = files(
    'public/const.h'
)

# Define the libconst library so it can be linked against by other parts of the build system
libconst = library('const',
    const_sources, 
    include_directories: include_directories('public'),
    cpp_args: ['-fvisibility=default'],
    dependencies: [const_data_dep],
    install : true)

const_dep = declare_dependency(
    include_directories: include_directories('public'),
    link_with: libconst,
)

# Make headers accessible
install_headers(const_headers, subdir : 'fourdst/constants')
