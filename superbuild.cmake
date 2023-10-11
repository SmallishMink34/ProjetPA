# Install SDL2 and SDL2_image
execute_process(COMMAND sudo apt-get install -y libsdl2-dev libsdl2-image-dev)

# Include the main CMakeLists.txt for your project
add_subdirectory(${CMAKE_SOURCE_DIR})
