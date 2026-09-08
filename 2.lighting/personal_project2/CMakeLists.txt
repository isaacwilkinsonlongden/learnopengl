cmake_minimum_required(VERSION 3.10)
project(gallery)

# objects/*.h use C++17 inline variables, so this is required rather than
# a preference -- don't rely on the compiler's default standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# default to an optimized build when the user hasn't picked one
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# source files
add_executable(gallery main.cpp glad.c stb_image.cpp)

# copy shader files to build directory (object shader + light shader)
foreach(SHADER shader.vs shader.fs light_shader.vs light_shader.fs)
    configure_file(${SHADER} ${SHADER} COPYONLY)
endforeach()

# copy texture assets to build directory (diffuse color map + specular map per material)
foreach(TEXTURE
    Bricks097_1K-JPG_Color.jpg
    Bricks097_1K_specmap.png
    Concrete042A_1K-JPG_Color.jpg
    Concrete042A_1K_specmap.png
    Wood039_1K-JPG_Color.jpg
    Wood039_1K_specmap.png
)
    configure_file(assets/${TEXTURE} ${TEXTURE} COPYONLY)
endforeach()

# where to find headers
target_include_directories(gallery PRIVATE $ENV{HOME}/dev/opengl-libs/Include)

# where to find libraries
target_link_directories(gallery PRIVATE $ENV{HOME}/dev/opengl-libs/Libs)

# which libraries to link
target_link_libraries(gallery
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)
