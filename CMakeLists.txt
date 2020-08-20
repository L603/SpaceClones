cmake_minimum_required(VERSION 3.16.0)

# El nombre del proyecto
project(space-clones
	VERSION 1.0
	DESCRIPTION "Un clón de space invaders"
	HOMEPAGE_URL "https://github.com/L603/SpaceClones"
	LANGUAGES "CXX"
)

include(GNUInstallDirs)
include(FindPkgConfig)
include(CPack)

# Variables por default
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON
	CACHE BOOL
	"La compilación incremental demora más si está en OFF."
)
set(CMAKE_UNITY_BUILD OFF
	CACHE BOOL
	"ccls no funciona con esto en ON."
)

# El programa en sí
add_executable(${PROJECT_NAME})

# Sín esto el target_sources() no resuelve path's relativos.
cmake_policy(SET CMP0076 NEW)
# En src/CMakeLists.txt se declara los source files.
add_subdirectory(src)

# El estandard de C++
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 17
)

# Estos macros sirven para cargar los assets
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")
set(BUILD_DATA_DIR "${CMAKE_BINARY_DIR}/share")
set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
set(BUILD_BIN_DIR "${CMAKE_BINARY_DIR}")

# Flags para el compilador
if(NOT DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS "-Wall -g")
endif()

# El header de configuración
target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_BINARY_DIR}/
)
configure_file(config.h.in
	${CMAKE_BINARY_DIR}/config.h
)

pkg_check_modules(shared
	REQUIRED IMPORTED_TARGET
		sfml-all
		fontconfig
)

# Linkeado
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		PkgConfig::shared
)

# }}}
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

# Configuración para el paquete .deb
configure_file(CPackConfig.cmake.in
	${CMAKE_BINARY_DIR}/CPackConfig.cmake
)
