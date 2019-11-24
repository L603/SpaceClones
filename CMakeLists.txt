cmake_minimum_required(VERSION 3.10.0)

# Módulos de cmake {{{
include(GNUInstallDirs)
include(FindPkgConfig)

# }}}
# El nombre del proyecto
project(space-clones)

# Unas cuantas definiciones {{{
set(SRC_DIR ./src)
set(SOURCES
	${SRC_DIR}/main.cpp
	${SRC_DIR}/scene.cpp
	${SRC_DIR}/gameObject.cpp
	${SRC_DIR}/bala.cpp
	${SRC_DIR}/nave.cpp
	${SRC_DIR}/rigidBody.cpp
	${SRC_DIR}/damageable.cpp
	${SRC_DIR}/escudos.cpp
	${SRC_DIR}/alien.cpp
	)
set(CMAKE_CXX_STANDARD 17)
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")
set(BUILD_DATA_DIR "${CMAKE_BINARY_DIR}/share")

# }}}
# Flags para el compilador {{{
if(NOT DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS "-Wall -g")
endif()

# }}}

# El header de configuración
include_directories(${CMAKE_BINARY_DIR}/)# Para el config.h
configure_file(config.h.cmake ${CMAKE_BINARY_DIR}/config.h )

# El programa en sí
add_executable(${PROJECT_NAME} ${SOURCES})


# Buscando y linkeando SFML {{{
pkg_check_modules(SFML sfml-all)

target_link_libraries(${PROJECT_NAME}
	sfml-system
	sfml-window
	sfml-graphics
)

# }}}
# Definiciones para la instalación {{{
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
#}}}
