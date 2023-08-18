cmake_minimum_required(VERSION 3.24)
project(Steele)

set(CMAKE_CXX_STANDARD 17)


include_directories( 
	Source
	godot-cpp/godot-headers/ 
	godot-cpp/include/ 
	godot-cpp/include/gen/ 
	godot-cpp/include/core/  
	godot-cpp/include/
	Library)


file(GLOB_RECURSE GODOT_SRC
	"godot-cpp/gdextension/*.cpp"
	"godot-cpp/gdextension/*.hpp"
	"godot-cpp/src/*.cpp"
	"godot-cpp/src/*.hpp"
	"godot-cpp/gen/*.cpp"
	"godot-cpp/gen/*.hpp"
)

file(GLOB_RECURSE LIBRARIES_SRC
	"Library/*.cpp"
	"Library/*.hpp"
)

file(GLOB_RECURSE MAIN_SOURCE
	"Source/*.cpp"
	"Source/*.h"
)

file(GLOB_RECURSE TEST_SOURCE
	"Tests/*.cpp"
	"Tests/*.h"
)

add_executable(Steele ${LIBRARIES_SRC} ${MAIN_SOURCE})
add_executable(Steele_With_Godot ${LIBRARIES_SRC} ${GODOT_SRC} ${MAIN_SOURCE}  main.cpp)
add_executable(Steele_UnitTest ${LIBRARIES_SRC} ${GODOT_SRC} ${MAIN_SOURCE} ${TEST_SOURCE})

target_include_directories(Steele PUBLIC
	godot-cpp/include
	godot-cpp/gen/include
	godot-cpp/gdextension
)

target_include_directories(Steele_With_Godot PUBLIC
	godot-cpp/include
	godot-cpp/gen/include
	godot-cpp/gdextension
)

target_include_directories(Steele_UnitTest PUBLIC
	godot-cpp/include
	godot-cpp/gen/include
	godot-cpp/gdextension
	Tests
)

target_link_libraries(Steele ${CMAKE_SOURCE_DIR}/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a)

