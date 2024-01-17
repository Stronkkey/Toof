servers_source_files = files(
	'rendering_server.cpp',
	'physics_server.cpp',
)

servers_headers = files(
	'rendering_server.hpp',
	'physics_server.hpp',
)

subdir('rendering')
subdir('physics')

servers_source_files += (servers_rendering_source_files + servers_physics_source_files)
servers_headers += (servers_rendering_headers + servers_physics_headers)