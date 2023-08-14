cmake_minimum_required(VERSION 3.9.0)

project(sdl2-shooter)

find_package(SDL2 REQUIRED)

add_executable(sdl2-shooter
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/game_timer.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/game.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/soa.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/entities/entities_game.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_animation.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_camera.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_movement.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_physics.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_tilemap.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_despawn.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_transform.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/systems/systems_sdl2.c)
target_include_directories(sdl2-shooter
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl2-shooter
	${SDL2_LIBRARIES}
	m)

add_executable(sdl2-shooter-test
	${CMAKE_CURRENT_SOURCE_DIR}/test/main.c)
target_include_directories(sdl2-shooter-test
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(NAME sdl2-shooter-test
	COMMAND sdl2-shooter-test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_LIST_DIR})

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
