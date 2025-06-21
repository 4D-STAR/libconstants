data_file = files('const.dat')
command_file = files('format.sh')
output_file = meson.current_build_dir() + '/embedded_constants.h'

embedded_constants_h = custom_target('embed_constants',
    input: data_file,
    output: 'embedded_constants.h',
    command: ['sh', '-c', command_file[0].full_path()+' @INPUT@ ' + output_file, '@INPUT@', '@OUTPUT@']
)

# Ensure the generated header is included
const_data_header = include_directories('.')

const_data_dep = declare_dependency(
    include_directories: const_data_header,
    sources: embedded_constants_h
)
