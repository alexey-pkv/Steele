cmake_minimum_required(VERSION 3.24)
project(Steele)

set(CMAKE_CXX_STANDARD 17)
set(CXX_WARNINGS "-Wno-reorder")


include_directories( 
	Source
	../godot-cpp/include/
	../godot-cpp/include/godot_cpp
	../godot-cpp/gen/include
	../godot-cpp/gdextension
	Library)


file(GLOB_RECURSE GODOT_SRC
	"../godot-cpp/gdextension/*.cpp"
	"../godot-cpp/gdextension/*.hpp"
	"../godot-cpp/src/*.cpp"
	"../godot-cpp/src/*.hpp"
	"../godot-cpp/gen/*.cpp"
	"../godot-cpp/gen/*.hpp"
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


########################
### Steele extension ###
########################
add_library(Steele SHARED ${LIBRARIES_SRC} ${MAIN_SOURCE})
set_target_properties(Steele PROPERTIES 
	OUTPUT_NAME "steele"
	LIBRARY_OUTPUT_DIRECTORY "../bin")

target_link_libraries(Steele ${CMAKE_SOURCE_DIR}/../godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a)

# Copy files from 
file(GLOB GD_EXTENSION_CONFIG GDExtensions/*.gdextension)
foreach(ConfigFile IN LISTS GD_EXTENSION_CONFIG)
	add_custom_command(TARGET Steele POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${ConfigFile} ${CMAKE_SOURCE_DIR}/bin
		COMMENT "Copying header: ${ConfigFile} to bin/"
	)
endforeach ()

file(GLOB OUTPUT_FILES bin/*.gdextension bin/libsteele.so)
foreach(File IN LISTS OUTPUT_FILES)
	add_custom_command(TARGET Steele POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${File} ${CMAKE_SOURCE_DIR}/../Steele-Godot/Extensions/
		COMMENT "Copying to godot project: ${File} to ../Steele-Godot/Extensions/"
	)
endforeach ()


###########################
### Main.cpp executable ###
###########################
add_executable(Steele_With_Godot ${LIBRARIES_SRC} ${GODOT_SRC} ${MAIN_SOURCE}  main.cpp)


#############
### Tests ###
#############
add_executable(Steele_UnitTest ${LIBRARIES_SRC} ${GODOT_SRC} ${MAIN_SOURCE} ${TEST_SOURCE})
target_include_directories(Steele_UnitTest PUBLIC Tests)


#############
### Godot ###
#############
add_custom_target(Godot_Build
	COMMAND scons platform=linux -j4
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Building godot library"
)