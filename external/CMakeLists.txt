if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### SOIL ###

set(SOIL_SOURCES
	soil2/src/SOIL2/SOIL2.c
	soil2/src/SOIL2/etc1_utils.c
	soil2/src/SOIL2/image_DXT.c
	soil2/src/SOIL2/image_helper.c
)

add_library(SOIL STATIC ${SOIL_SOURCES})

### JSONCPP ###

add_library(JSONCPP STATIC jsoncpp/jsoncpp.cpp)

### GLEW ###

add_library(GLEW STATIC glew-1.13.0/src/glew.c)

target_link_libraries(GLEW
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

### ASSIMP ###

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(assimp)
