cmake_minimum_required(VERSION 3.10)
project(SimpleDrawApp)

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/menu.cpp
    src/toolbar.cpp
    src/drawCanvas.cpp
    src/consolePrinter.cpp
)

# Set paths to the dependencies
set(SFML_DIR "${CMAKE_SOURCE_DIR}/deps/sfml")
set(TGUI_DIR "${CMAKE_SOURCE_DIR}/deps/tgui")
set(FREETYPE_DIR "${CMAKE_SOURCE_DIR}/deps/freetype")

# Debug/Release configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build")
    add_executable(SimpleDrawApp ${SOURCE_FILES})
    target_link_libraries(SimpleDrawApp PRIVATE
        ${TGUI_DIR}/lib/libtgui-s-d.a
        ${SFML_DIR}/lib/libsfml-graphics-s-d.a
        ${SFML_DIR}/lib/libsfml-window-s-d.a
        ${SFML_DIR}/lib/libsfml-system-s-d.a
    )
    set(EXE_NAME SimpleDrawApp-Debug)
    target_compile_definitions(SimpleDrawApp PRIVATE RELEASE_BUILD)
else()
    message(STATUS "Configuring Release build")
    add_executable(SimpleDrawApp WIN32 ${SOURCE_FILES} resource.o)
    target_link_libraries(SimpleDrawApp PRIVATE
        ${TGUI_DIR}/lib/libtgui-s.a
        ${SFML_DIR}/lib/libsfml-graphics-s.a
        ${SFML_DIR}/lib/libsfml-window-s.a
        ${SFML_DIR}/lib/libsfml-system-s.a
    )
    set(EXE_NAME SimpleDrawApp)
    target_compile_definitions(SimpleDrawApp PRIVATE DEBUG_BUILD)
endif()

# Define static build flags
add_definitions(-DSFML_STATIC -DTGUI_STATIC)

# Include directories
target_include_directories(SimpleDrawApp PRIVATE
# set(BASE_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_DIR}/include
    ${TGUI_DIR}/include
    ${FREETYPE_DIR}/include
)

# Link base libraries
target_link_libraries(SimpleDrawApp PRIVATE
    ${FREETYPE_DIR}/lib/libfreetype.a
    -lwinmm
    -lgdi32
    -lopengl32
    -luuid
)

# Set linker flags
set_target_properties(SimpleDrawApp PROPERTIES
    LINK_FLAGS "-static-libgcc -static-libstdc++ -static"
    RUNTIME_OUTPUT_NAME "${EXE_NAME}"
)