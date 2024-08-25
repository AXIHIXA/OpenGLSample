cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL)
set(CMAKE_CXX_STANDARD 17)

# packages to find

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

# all sources

set(ALL_INCLUDE_DIRS
        ${GLEW_INCLUDE_DIRS}
        ${OPENCV_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        include
        )

set(ALL_LIBRARIES
        ${OpenCV_LIBS}
        dl
        GLEW::GLEW
        glfw
        OpenGL::GL
        OpenGL::OpenGL
        OpenGL::GLU
        OpenGL::GLX
        OpenGL::EGL
        pthread
        )

# all definitions and options

set(ALL_COMPILE_DEFS

        )

set(ALL_COMPILE_OPTS

        )

# executable target(s)

add_executable(04_hello_window
        src/glad/glad.c
        src/learnopengl/04_hello_window.cpp
        )
target_compile_definitions(04_hello_window PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(04_hello_window PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(04_hello_window PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(04_hello_window ${ALL_LIBRARIES})

add_executable(05_hello_rectangle
        src/glad/glad.c
        src/learnopengl/05_hello_rectangle.cpp
        )
target_compile_definitions(05_hello_rectangle PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(05_hello_rectangle PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(05_hello_rectangle PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(05_hello_rectangle ${ALL_LIBRARIES})

add_executable(06_shaders
        include/learnopengl/shader.h
        src/glad/glad.c
        src/learnopengl/06_shaders.cpp
        )
target_compile_definitions(06_shaders PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(06_shaders PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(06_shaders PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(06_shaders ${ALL_LIBRARIES})

add_executable(07_textures
        include/learnopengl/shader.h
        src/glad/glad.c
        src/learnopengl/07_textures.cpp
        )
target_compile_definitions(07_textures PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(07_textures PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(07_textures PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(07_textures ${ALL_LIBRARIES})

add_executable(08_transformations
        include/learnopengl/shader.h
        src/glad/glad.c
        src/learnopengl/08_transformations.cpp
        )
target_compile_definitions(08_transformations PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(08_transformations PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(08_transformations PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(08_transformations ${ALL_LIBRARIES})

add_executable(09_coordinate_systems
        include/learnopengl/shader.h
        src/glad/glad.c
        src/learnopengl/09_coordinate_systems.cpp
        )
target_compile_definitions(09_coordinate_systems PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(09_coordinate_systems PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(09_coordinate_systems PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(09_coordinate_systems ${ALL_LIBRARIES})

add_executable(10_camera
        include/learnopengl/camera.h
        include/learnopengl/shader.h
        src/glad/glad.c
        src/learnopengl/10_camera.cpp
        )
target_compile_definitions(10_camera PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(10_camera PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(10_camera PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(10_camera ${ALL_LIBRARIES})
