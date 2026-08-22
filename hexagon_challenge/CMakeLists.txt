cmake_minimum_required(VERSION 3.10)
project(hexagon_challenge)

# source files 
add_executable(hexagon_challenge main.cpp glad.c)

# copy shaders to build
configure_file(shader.vs shader.vs COPYONLY)
configure_file(shader.fs shader.fs COPYONLY)

# where to find headers
target_include_directories(hexagon_challenge PRIVATE $ENV{HOME}/dev/opengl-libs/Include)

# where to find libraries
target_link_directories(hexagon_challenge PRIVATE $ENV{HOME}/dev/opengl-libs/Libs)

# which libraries to link
target_link_libraries(hexagon_challenge
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)