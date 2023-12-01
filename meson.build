project(
  'sdl_libs',
  'cpp',
  version: '1.0.0',
  default_options : ['warning_level=3']
)

project_description = 'Simple wrapper for sdl2'

project_headers = [
  'items/item.hpp',
  'items/rendering_item.hpp',
  'items/sprite.hpp',
  'types/vector2.hpp',
  'types/rect2.hpp',
  'types/uid.hpp',
  'types/ref.hpp',
  'tree.hpp',
  'rendering_server.hpp',
  'window.hpp'
]

project_source_files = [
  'items/item.cpp',
  'items/rendering_item.cpp',
  'items/sprite.cpp',
  'types/rect2.cpp',
  'types/vector2.cpp',
  'types/uid.cpp',
  'rendering_server.cpp',
  'tree.cpp',
  'window.cpp'
]

project_test_files = [
]

project_dependencies = [
  dependency('sdl2'),
  dependency('sdl2_image')
]

build_args = [
]

public_headers = include_directories('./')

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
  link_with : project_target
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


# ==========
# Unit Tests
# ==========

if not meson.is_subproject()
  add_languages('cpp')
  subdir('tests')

  test('all_tests',
    executable(
      'run_tests',
      files(project_test_files),
      dependencies : [project_dep, test_dep],
      install : false
    )
  )
endif
