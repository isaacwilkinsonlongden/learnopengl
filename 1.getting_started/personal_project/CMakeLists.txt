 cmake_minimum_required(VERSION 3.10)
 project(gallery)

 # source files 
 add_executable(gallery main.cpp glad.c stb_image.cpp)

 # copy shader files to build directory
 configure_file(shader.vs shader.vs COPYONLY)
 configure_file(shader.fs shader.fs COPYONLY)
 configure_file(assets/Bricks097_1K-JPG_Color.jpg Bricks097_1K-JPG_Color.jpg COPYONLY)
 configure_file(assets/Concrete042A_1K-JPG_Color.jpg Concrete042A_1K-JPG_Color.jpg COPYONLY)

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