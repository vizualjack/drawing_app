cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(SOURCE_FILES
    src/main.cpp
    src/menu.cpp
    src/toolbar.cpp
    src/drawCanvas.cpp
    src/consolePrinter.cpp
)

####### BUILDS
#### RELEASE VERSION
set(CMAKE_BUILD_TYPE Release)
add_executable(MyProject WIN32 ${SOURCE_FILES})
# add_executable(MyProject WIN32 src/main.cpp)
#### DEBUG VERSION
# set(CMAKE_BUILD_TYPE Debug)
# add_executable(MyProject ${SOURCE_FILES})
########


# Set paths to the dependencies
set(SFML_DIR "${CMAKE_SOURCE_DIR}/deps/sfml")
set(TGUI_DIR "${CMAKE_SOURCE_DIR}/deps/tgui")
set(FREETYPE_DIR "${CMAKE_SOURCE_DIR}/deps/freetype")


# Define static build flags
add_definitions(-DSFML_STATIC -DTGUI_STATIC)

# Include directories
target_include_directories(MyProject PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_DIR}/include
    ${TGUI_DIR}/include
    ${FREETYPE_DIR}/include
)

# Link libraries
target_link_libraries(MyProject PRIVATE
# RELEASE
    # ${TGUI_DIR}/lib/libtgui-s.a
    # ${SFML_DIR}/lib/libsfml-graphics-s.a
    # ${SFML_DIR}/lib/libsfml-window-s.a
    # ${SFML_DIR}/lib/libsfml-system-s.a
# DEBUG
    ${TGUI_DIR}/lib/libtgui-s-d.a
    ${SFML_DIR}/lib/libsfml-graphics-s-d.a
    ${SFML_DIR}/lib/libsfml-window-s-d.a
    ${SFML_DIR}/lib/libsfml-system-s-d.a
    ${FREETYPE_DIR}/lib/libfreetype.a
    -lwinmm
    -lgdi32
    -lopengl32
    -luuid
)


# Set linker flags
set_target_properties(MyProject PROPERTIES
    LINK_FLAGS "-static-libgcc -static-libstdc++ -static"
)