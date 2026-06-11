# ***********************************************************************
#
#   Copyright (C) 2025 -- The 4D-STAR Collaboration
#   File Author: Emily Boudreaux
#   Last Modified: June 21, 2025
#
#   libconstants is free software; you can use it and/or modify
#   it under the terms and restrictions the GNU General Library Public
#   License version 3 (GPLv3) as published by the Free Software Foundation.
#
#   libconstants is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#   See the GNU Library General Public License for more details.
#
#   You should have received a copy of the GNU Library General Public License
#   along with this software; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
# *********************************************************************** #
project('libconstants', 'cpp', version: 'v1.1.6', default_options: ['cpp_std=c++23'], meson_version: '>=1.5.0')

# Add default visibility for all C++ targets
add_project_arguments('-fvisibility=default', language: 'cpp')

if get_option('build_python')
    local_py_install = import('python').find_installation('python3', pure: false)
    fourdst_pkg = local_py_install.get_install_dir() / 'fourdst'

    constants_libdir             = fourdst_pkg / 'lib'
    constants_header_install_dir = fourdst_pkg / 'include' / 'fourdst' / 'constants'

    vendor_lib_dir             = fourdst_pkg / 'lib' / 'vendor'
    vendor_header_dir          = fourdst_pkg / 'include' / 'fourdst' / 'vendor'

    message('Installing libconfig in python mode. Install locations are...')
else
    constants_libdir             = get_option('libdir')
    constants_header_install_dir = get_option('includedir') / 'fourdst' / 'constants'

    message('Installing libconfig in non python (normal) mode. Install locations are...')
endif
message('    Libraries: ' + constants_libdir)
message('    Headers:   ' + constants_header_install_dir)


cpp = meson.get_compiler('cpp')

subdir('assets/static')

subdir('src')

if get_option('build_tests')
  subdir('tests')
endif

if get_option('build_examples')
  subdir('examples')
endif

if get_option('pkg_config')
    message('Generating pkg-config file for libconstants...')
    pkg = import('pkgconfig')
    pkg.generate(
        name: 'libconstants',
        description: 'Physical Constants for SERiF and related projects',
        version: meson.project_version(),
        libraries: [libconst, '-Wl,-rpath,${libdir}'],
        filebase: 'fourdst_constants',
        install_dir: join_paths(get_option('libdir'), 'pkgconfig')
    )
endif

