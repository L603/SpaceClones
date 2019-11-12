cmake_minimum_required(VERSION 3.10.0)

project(clone)

set(SRC_DIR ./src)
set(SOURCES
	${SRC_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

include(FindPkgConfig)
pkg_check_modules(SFML sfml-all)

target_link_libraries(${PROJECT_NAME} ${SFML})