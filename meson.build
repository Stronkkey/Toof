project(
  'sdl_libs',
  'cpp',
  version: '1.0.0',
  default_options : ['warning_level=3']
)

project_description = 'Simple wrapper for sdl2'

rendering_server_headers = [
  'servers/rendering_server.hpp',
  'servers/rendering/2d/canvas_item.hpp',
  'servers/rendering/2d/drawing_item.hpp',
  'servers/rendering/viewport.hpp',
  'servers/rendering/window.hpp',
  'servers/rendering/texture.hpp'
]

rendering_server_sources = [
  'servers/rendering_server.cpp',
  'servers/rendering/2d/canvas_item.cpp',
  'servers/rendering/2d/drawing_item.cpp',
  'servers/rendering/viewport.cpp',
  'servers/rendering/window.cpp'
]

resources_headers = [
  'resources/texture2d.hpp'
]

resources_sources = [
  'resources/texture2d.cpp'
]

item_headers = [
  'items/tree.hpp',
  'items/item.hpp',
  'items/rendering_item.hpp',
  'items/sprite.hpp',
  'items/camera_item.hpp',
]

item_sources = [
  'items/tree.cpp',
  'items/item.cpp',
  'items/rendering_item.cpp',
  'items/sprite.cpp',
  'items/camera_item.cpp',
]

input_headers = [
  'input/input_manager.hpp'
]

input_sources = [
  'input/input_manager.cpp'
]

math_headers = [
  'core/math/math_defs.hpp',
  'core/math/vector2.hpp',
  'core/math/rect2.hpp',
  'core/math/transform2d.hpp',
  'core/math/color.hpp',
]

math_sources = [
  'core/math/math_defs.cpp',
  'core/math/vector2.cpp',
  'core/math/rect2.cpp',
  'core/math/transform2d.cpp',
  'core/math/color.cpp',
]

core_headers = [
  math_headers,
  'core/utility_functions.hpp'
]

core_sources = [
  math_sources,
  'core/utility_functions.cpp'
]

project_headers = [
  core_headers,
  input_headers,
  item_headers,
  resources_headers,
  rendering_server_headers,
]

project_source_files = [
  core_sources,
  input_sources,
  item_sources,
  resources_sources,
  rendering_server_sources,
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
