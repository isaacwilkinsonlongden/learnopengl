 cmake_minimum_required(VERSION 3.10)
 project(colors)

 # source files 
 add_executable(colors main.cpp glad.c)

 # copy shader files to build directory
 configure_file(lighting_shader.vs lighting_shader.vs COPYONLY)
 configure_file(lighting_shader.fs lighting_shader.fs COPYONLY)

 # where to find headers 
 target_include_directories(colors PRIVATE $ENV{HOME}/dev/opengl-libs/Include)

 # where to find libraries 
 target_link_directories(colors PRIVATE $ENV{HOME}/dev/opengl-libs/Libs)

 # which libraries to link
 target_link_libraries(colors
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)