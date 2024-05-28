project(
  'Toof',
  'cpp',
  version: '1.0.0',
  default_options : ['warning_level=3']
)

project_description = 'Toof Engine - somewhat simple 2D game engine.'

subdir('core')
subdir('input')
subdir('scene')
subdir('servers')
subdir('tests')
subdir('physics')

project_headers = [
  core_headers,
  input_headers,
  scene_headers,
  servers_headers,
  physics_headers,
]

project_source_files = [
  core_source_files,
  input_source_files,
  scene_source_files,
  servers_source_files,
  physics_source_files,
]

test_source_files = [
  project_source_files,
  tests_source_files,
]

test_headers = [
  project_headers,
  tests_headers,
]

sdl_dependency = dependency('sdl2')
sdl_image_dependency = dependency('sdl2_image')
box2d_dependency = dependency('box2d')
cereal_dependency = dependency('cereal')
stringify_dependency = dependency('stringify', fallback: ['stringify', 'project_dependency'])

project_dependencies = [
  sdl_dependency,
  sdl_image_dependency,
  cereal_dependency,
  stringify_dependency
]

build_args = [
]

project_variables = {
}

public_headers = include_directories('./')

double_precision_enabled = get_option('double_precision').enabled()
int_64bit_enabled = get_option('int_64bit').enabled()
physics_enabled = get_option('physics').enabled()
box2d_enabled = get_option('box2d').enabled()

if double_precision_enabled
  build_args += '-D TOOF_REAL_T_IS_DOUBLE'
  project_variables += {'double': 'true'}
else
  project_variables += {'double': 'false'}
endif

if physics_enabled
  build_args += '-D TOOF_PHYSICS_ENABLED'
  project_variables += {'physics': 'true'}
else
  if not box2d_enabled
    project_variables += {'physics': 'false'}
  endif
endif

if box2d_enabled
  if not physics_enabled
    build_args += '-D TOOF_PHYSICS_ENABLED'
    project_variables += {'physics': 'true'}
  endif

  build_args += '-D TOOF_B2_ENABLED'
  project_variables += {'box2d': 'true'}
  project_dependencies += box2d_dependency
else
  project_variables += {'box2d': 'false'}
endif

if int_64bit_enabled
  build_args += '-D TOOF_INT_IS_64BIT'
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

base_test_build = executable(
  meson.project_name() + 'test',
  test_source_files,
  dependencies: project_dependencies,
  install: false,
  cpp_args: build_args
)

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

test(
  'Success',
  base_test_build,
  args: ['success'],
  verbose: true
)

test(
  'Fail',
  base_test_build,
  args: ['fail'],
  verbose: true,
  should_fail: true,
)

test(
  'Math',
  base_test_build,
  args: ['math'],
  verbose: true,
)

test(
  'Color',
  base_test_build,
  args: ['color'],
  verbose: true,
)
