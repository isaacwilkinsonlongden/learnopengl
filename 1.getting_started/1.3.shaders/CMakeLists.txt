cmake_minimum_required(VERSION 3.10)
project(hello_window)

# Your source file(s)
add_executable(hello_window main.cpp glad.c)

configure_file(shader.vs shader.vs COPYONLY)
configure_file(shader.fs shader.fs COPYONLY)

# Where to find headers (equivalent of -I)
target_include_directories(hello_window PRIVATE $ENV{HOME}/dev/opengl-libs/Include)

# Where to find libraries (equivalent of -L)
target_link_directories(hello_window PRIVATE $ENV{HOME}/dev/opengl-libs/Libs)

# Which libraries to link (equivalent of -l flags)
target_link_libraries(hello_window
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)