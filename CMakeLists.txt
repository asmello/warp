cmake_minimum_required (VERSION 2.6)
project (Warp)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/cmake_modules")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

find_package(OpenGL REQUIRED)

if(APPLE)
	find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)
else(APPLE)
	set(SFML_STATIC_LIBRARIES TRUE)
endif(APPLE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(
	include/
	external/glm/
	external/jsoncpp/
	external/glew-1.13.0/include/
	external/assimp/include/
	external/soil2/src/SOIL2/
	${SFML_INCLUDE_DIR}
)

# Compile external dependencies
add_subdirectory (external)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES}
	GLEW
	SOIL
	assimp
)

if(APPLE)
	list(APPEND ALL_LIBS ${COREFOUNDATION_FRAMEWORK})
endif(APPLE)

add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# MAIN
set(WARP_SOURCES
	src/util.cpp
	src/main.cpp
	src/Mesh.cpp
	src/Input.cpp
	src/Scene.cpp
	src/Shader.cpp
	src/Camera.cpp
	src/Texture.cpp
	src/Renderer.cpp
	src/GameLoop.cpp
	src/Material.cpp
	src/Transform.cpp
	src/Component.cpp
	src/GameObject.cpp
	src/MeshManager.cpp
	src/MeshRenderer.cpp
	src/SceneManager.cpp
	src/SceneRenderer.cpp
	src/ShaderManager.cpp
	src/CameraManager.cpp
	src/TextureManager.cpp
	src/MaterialManager.cpp
	src/GameObjectManager.cpp
)
set(WARP_HEADERS
	include/util.hpp
	include/Mesh.hpp
	include/Input.hpp
	include/Scene.hpp
	include/Object.hpp
	include/Shader.hpp
	include/Camera.hpp
	include/Texture.hpp
	include/Material.hpp
	include/Renderer.hpp
	include/GameLoop.hpp
	include/Transform.hpp
	include/Component.hpp
	include/Singleton.hpp
	include/GameObject.hpp
	include/Identifier.hpp
	include/MeshManager.hpp
	include/MeshRenderer.hpp
	include/SceneManager.hpp
	include/InputListener.hpp
	include/SceneRenderer.hpp
	include/ShaderManager.hpp
	include/CameraManager.hpp
	include/TextureManager.hpp
	include/MaterialManager.hpp
	include/ResourceManager.hpp
	include/GameObjectManager.hpp
)
add_executable(Warp ${WARP_SOURCES} ${WARP_HEADERS})
target_link_libraries(Warp ${ALL_LIBS})
set_property(TARGET Warp PROPERTY CXX_STANDARD 11)

# Xcode and Visual working directories
set_target_properties(Warp PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
create_target_launcher(Warp WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

if(${CMAKE_GENERATOR} MATCHES "Xcode")
	file(COPY "resources" DESTINATION ".")
endif(${CMAKE_GENERATOR} MATCHES "Xcode")

# Copy resource files
# if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
# add_custom_command(
#    TARGET Warp POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/resources/" "${CMAKE_CURRENT_SOURCE_DIR}/"
# )
# elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )
#
# endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
