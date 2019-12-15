cmake_minimum_required(VERSION 3.13.0)

# Módulos de cmake {{{
include(GNUInstallDirs)
include(FindPkgConfig)
include(CPack)

# }}}
# El nombre del proyecto
project(space-clones
	VERSION 1.0
	DESCRIPTION "Un clón de space invaders"
	HOMEPAGE_URL "https://github.com/L603/SpaceClones"
	LANGUAGES "CXX"
)

# El programa en sí
add_executable(${PROJECT_NAME})

# Sín esto el target_sources() no resuelve path's relativos.
cmake_policy(SET CMP0076 NEW)
# En src/CMakeLists.txt se declara los source files.
add_subdirectory(src)

# El estandard de C++
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Estos macros sirven para cargar los assets {{{
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")
set(BUILD_DATA_DIR "${CMAKE_BINARY_DIR}/share")
set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
set(BUILD_BIN_DIR "${CMAKE_BINARY_DIR}")

# }}}
# Flags para el compilador {{{
if(NOT DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS "-Wall -g")
endif()

# }}}

# El header de configuración
target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_BINARY_DIR}/
)
configure_file(config.h.in
	${CMAKE_BINARY_DIR}/config.h
)

# Buscando y linkeando SFML {{{
pkg_check_modules(SFML REQUIRED sfml-all)
pkg_check_modules(FONTS REQUIRED fontconfig)

target_link_libraries(${PROJECT_NAME}
	${SFML_LIBRARIES}
	${FONTS_LIBRARIES}
	stdc++fs
)

# }}}
# Definiciones para la instalación {{{
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
#}}}

# Configuración para el paquete .deb
configure_file(CPackConfig.cmake.in
	${CMAKE_BINARY_DIR}/CPackConfig.cmake
)
