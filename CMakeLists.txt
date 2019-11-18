cmake_minimum_required(VERSION 3.10.0)

include(GNUInstallDirs)
include(FindPkgConfig)

# El nombre del proyecto
project(clone)

# Unas cuantas definiciones
set(SRC_DIR ./src)
set(SOURCES
	${SRC_DIR}/main.cpp
	${SRC_DIR}/scene.cpp
	${SRC_DIR}/gameObject.cpp
	${SRC_DIR}/bala.cpp
	${SRC_DIR}/nave.cpp
	${SRC_DIR}/rigidBody.cpp
	${SRC_DIR}/damageable.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Buscando y linkeando SFML y Box2d
pkg_check_modules(SFML sfml-all)


target_link_libraries(${PROJECT_NAME}
	sfml-system
	sfml-window
	sfml-graphics
)

# Install target
install(TARGETS clone
	DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

