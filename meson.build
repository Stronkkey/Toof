project(
  'Toof',
  'cpp',
  version: '1.1.0',
  default_options : ['warning_level=3'],
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

option_args = [
]

build_args = [
]

public_headers = include_directories('./')

double_precision_enabled = get_option('double_precision').enabled()
int_64bit_allowed = get_option('int_64bit').allowed()
physics_allowed = get_option('physics').allowed()
box2d_allowed = get_option('box2d').allowed()
default_gravity_x = get_option('default_gravity_x').to_string() + '.0'
default_gravity_y = get_option('default_gravity_y').to_string() + '.0'
units_per_meters = get_option('physics_length_units_per_meter').to_string() + '.0f'
max_polygon_vertices = get_option('physics_max_polygon_vertices').to_string()
override_b2_user_settings_disabled = not get_option('override_b2_user_settings').allowed()

config_math = configuration_data()
config_physics = configuration_data()
config_b2 = configuration_data()

config_math.set10('TOOF_REAL_T_IS_DOUBLE', double_precision_enabled)
config_math.set10('TOOF_INT_IS_64BIT', int_64bit_allowed)

config_physics.set10('TOOF_PHYSICS_ENABLED', physics_allowed or box2d_allowed)
config_physics.set10('TOOF_B2_ENABLED', box2d_allowed)
config_physics.set10('B2_USER_SETTINGS', true)
config_physics.set('TOOF_DEFAULT_GRAVITY_X', default_gravity_x)
config_physics.set('TOOF_DEFAULT_GRAVITY_Y', default_gravity_y)
config_physics.set('TOOF_PHYSICS_LENGTH_UNITS_PER_METER', units_per_meters)
config_physics.set('TOOF_PHYSICS_MAX_POLYGON_VERICES', max_polygon_vertices)
config_physics.set10('TOOF_OVERRIDE_B2_USER_SETTINGS', override_b2_user_settings_disabled)

config_b2.set('units_per_meter', units_per_meters)
config_b2.set('max_polygon_vertices', max_polygon_vertices)

if box2d_allowed
  project_dependencies += box2d_dependency
endif

configure_file(
  output : 'toof_math_features.hpp',
  configuration : config_math,
)

configure_file(
	output : 'toof_physics_features.hpp',
	configuration : config_physics,
)

configure_file(
	input : 'physics/b2_user_settings.h.in',
	output : 'b2_user_settings.h',
	configuration : config_b2,
)

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
  compile_args : build_args,
  include_directories : public_headers,
  dependencies : project_dependencies,
  link_with : project_target,
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


pkg = import('pkgconfig')

pkg.generate(project_target, extra_cflags: build_args)