cmake_minimum_required(VERSION 3.10)
project(hello_triangle)

# Your source file(s)
add_executable(hello_triangle main.cpp glad.c)

# Where to find headers (equivalent of -I)
target_include_directories(hello_triangle PRIVATE $ENV{HOME}/dev/opengl-libs/Include)

# Where to find libraries (equivalent of -L)
target_link_directories(hello_triangle PRIVATE $ENV{HOME}/dev/opengl-libs/Libs)

# Which libraries to link (equivalent of -l flags)
target_link_libraries(hello_triangle
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)