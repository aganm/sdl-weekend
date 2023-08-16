cmake_minimum_required(VERSION 3.9.0)

project(sdl2-shooter)

#set(SANITIZE "-fsanitize=address")
set(CMAKE_C_FLAGS_DEBUG "-pipe -DDEBUG -O3 -g -ggdb ${SANITIZE}")
set(CMAKE_CXX_FLAGS_DEBUG "-pipe -DDEBUG -O3 -g -ggdb ${SANITIZE}")
set(CMAKE_C_FLAGS_RELEASE "-pipe -DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-pipe -DNDEBUG -O3")

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
	set(WARNINGS
		-Wall
		-Wextra)
	set(NO_WARNINGS
		-Wno-missing-braces)
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(WARNINGS
		-Wall
		-Wextra)
	set(NO_WARNINGS
		-Wno-missing-braces)
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	set(WARNINGS
		/W4)
	set(NO_WARNINGS
		/D_CRT_SECURE_NO_WARNINGS)
endif()

add_compile_options(
	${WARNINGS}
	${NO_WARNINGS})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_LIST_DIR})

find_package(OpenMP REQUIRED)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

find_package(SDL2 REQUIRED)

add_executable(sdl2-shooter
	${CMAKE_CURRENT_SOURCE_DIR}/framework/src/soa.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/game/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/game/game.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/entities/entities_game.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_animation.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_movement.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_physics.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_tilemap.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_despawn.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_bullet.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_transform.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_sdl2.c)
target_include_directories(sdl2-shooter
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/framework/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl2-shooter
	${SDL2_LIBRARIES}
	m)

add_executable(sdl2-shooter-test
	${CMAKE_CURRENT_SOURCE_DIR}/test/main.c)
target_include_directories(sdl2-shooter-test
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/framework/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(NAME sdl2-shooter-test
	COMMAND sdl2-shooter-test)

set(OUTPUT "bin")
set(OUTPUT_PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY	 ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT}
	LIBRARY_OUTPUT_DIRECTORY	 ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT})

set_target_properties(sdl2-shooter PROPERTIES ${OUTPUT_PROPERTIES})
set_target_properties(sdl2-shooter-test PROPERTIES ${OUTPUT_PROPERTIES})
