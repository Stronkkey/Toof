project(
  'sdl_libs',
  'cpp',
  version: '1.0.0',
  default_options : ['warning_level=3']
)

project_description = 'Simple wrapper for sdl2'

project_headers = [
  'rendering/rendering_server.hpp',
  'rendering/window.hpp',
  'rendering/texture.hpp',
  'rendering/canvas_item.hpp',
  'rendering/viewport.hpp',
  'rendering/drawing_item.hpp',
  'items/tree.cpp',
  'items/item.hpp',
  'items/rendering_item.hpp',
  'items/sprite.hpp',
  'types/math_defs.hpp',
  'types/vector2.hpp',
  'types/rect2.hpp',
  'types/transform2d.hpp',
  'types/color.hpp',
  'input/input_manager.hpp'
]

project_source_files = [
  'rendering/rendering_server.cpp',
  'rendering/window.cpp',
  'rendering/canvas_item.cpp',
  'rendering/texture.cpp',
  'rendering/viewport.cpp',
  'rendering/drawing_item.cpp',
  'items/tree.cpp',
  'items/item.cpp',
  'items/rendering_item.cpp',
  'items/sprite.cpp',
  'types/rect2.cpp',
  'types/vector2.cpp',
  'types/transform2d.cpp',
  'types/color.cpp',
  'types/utility_functions.cpp',
  'input/input_manager.cpp'
]

project_test_files = [
]

project_dependencies = [
  dependency('boost'),
  dependency('sdl2'),
  dependency('sdl2_image')
]

build_args = [
]

project_variables = {
}

public_headers = include_directories('./')

double_precision_enabled = get_option('double_precision').enabled()
int_64bit_enabled = get_option('int_64bit').enabled()

if double_precision_enabled
  build_args += ['-D REAL_T_IS_DOUBLE']
  project_variables += {'double': 'true'}
else
  project_variables += {'double': 'false'}
endif

if int_64bit_enabled
  build_args += ['-D INT_IS_64BIT']
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
