cmake_minimum_required (VERSION 2.6)
project (Warp)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/cmake_modules")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

find_package(OpenGL REQUIRED)

if(NOT APPLE)
	set(SFML_STATIC_LIBRARIES TRUE)
endif(NOT APPLE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(
	include/
	external/glm/
	external/glew-1.13.0/include/
	external/assimp/include/
	${SFML_INCLUDE_DIR}
)

# Compile external dependencies
add_subdirectory (external)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES}
	GLEW
	assimp
)

add_definitions(
	-DGLEW_STATIC
	-DSFML_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# MAIN
set(WARP_SOURCES
	src/main.cpp
	src/Mesh.cpp
	src/ResourcePath.cpp
	src/Shader.cpp
	src/SimpleRenderer.cpp
	src/util.cpp
)
add_executable(Warp ${WARP_SOURCES})
target_link_libraries(Warp ${ALL_LIBS})
set_property(TARGET Warp PROPERTY CXX_STANDARD 11)

# Xcode and Visual working directories
set_target_properties(Warp PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
create_target_launcher(Warp WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Copy resource files
# if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
# add_custom_command(
   # TARGET Warp POST_BUILD
   # COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/"
# )
# elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

# endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
