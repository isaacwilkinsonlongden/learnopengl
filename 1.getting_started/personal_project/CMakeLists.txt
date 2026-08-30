 cmake_minimum_required(VERSION 3.10)
 project(gallery)

 # source files 
 add_executable(gallery main.cpp glad.c)

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