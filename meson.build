project(
  'sdl_libs',
  'cpp',
  version: '1.0.0',
  default_options : ['warning_level=3']
)

project_description = 'Simple wrapper for sdl2'

subdir('core')
subdir('input')
subdir('items')
subdir('resources')
subdir('servers')

project_headers = [
  core_headers,
  input_headers,
  item_headers,
  resources_headers,
  servers_headers,
]

project_source_files = [
  core_source_files,
  input_source_files,
  item_source_files,
  resources_source_files,
  servers_source_files,
]

test_headers = [
  project_headers,
  'tests/test_geometry2d.hpp',
]

project_test_files = [
]

project_dependencies = [
  dependency('boost'),
  dependency('sdl2'),
  dependency('sdl2_image'),
  dependency('box2d'),
]

build_args = [
]

project_variables = {
}

public_headers = include_directories('./')

double_precision_enabled = get_option('double_precision').enabled()
int_64bit_enabled = get_option('int_64bit').enabled()
box2d_enabled = get_option('box2d').enabled()

if double_precision_enabled
  build_args += '-D REAL_T_IS_DOUBLE'
  project_variables += {'double': 'true'}
else
  project_variables += {'double': 'false'}
endif

if box2d_enabled
  build_args += '-D B2_INCLUDED'
  project_variables += {'b2': 'true'}
else
  project_variables += {'b2': 'false'}
endif

if int_64bit_enabled
  build_args += '-D INT_IS_64BIT'
  project_variables += {'int64': 'true'}
else
  project_variables += {'int64': 'false'}
endif

build_args += [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
]

project_target = shared_library(
  meson.project_name(),
  project_source_files,
  install : true,
  cpp_args : build_args,
  gnu_symbol_visibility : 'default',
  dependencies: project_dependencies,
  include_directories : public_headers,
)

project_dep = declare_dependency(
  include_directories: public_headers,
  link_with : project_target,
  variables: project_variables
)
set_variable(meson.project_name() + '_dep', project_dep)


# Make this library usable from the system's
# package manager.
install_headers(project_headers, subdir : meson.project_name())

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
  libraries : project_target,
)
