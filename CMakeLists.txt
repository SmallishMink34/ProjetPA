cmake_minimum_required(VERSION 3.10)
project(mon_programme)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_TTF REQUIRED)
# find_package(SDL2_mixer REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})



include(ExternalProject)

ExternalProject_Add(
    tmxlite
    PREFIX ${CMAKE_BINARY_DIR}/third-party
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG master
    UPDATE_DISCONNECTED TRUE
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    CONFIGURE_COMMAND "" 
    BUILD_COMMAND ""  
    INSTALL_COMMAND "" 
    LOG_DOWNLOAD ON 
)

ExternalProject_Get_Property(tmxlite SOURCE_DIR)


add_custom_target(clean_tmxlite
    COMMAND bash -c "find ${SOURCE_DIR} -mindepth 1 -maxdepth 1 ! -name 'tmxlite' -exec rm -rf {} +"
    DEPENDS tmxlite
)

add_custom_target(build_tmxlite
    COMMAND ${CMAKE_COMMAND} -E make_directory build
    COMMAND ${CMAKE_COMMAND} -E chdir build ${CMAKE_COMMAND} ..
    COMMAND ${CMAKE_COMMAND} --build build
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/third-party/src/tmxlite/tmxlite/
    DEPENDS tmxlite
)

add_custom_target(run
    COMMAND bash -c "cd ../"
    COMMAND bash -c "./mon_programme"
    DEPENDS mon_programme
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Lancement du programme"
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(SRCS main.cpp lib/Variables/variables.cpp lib/world/world.cpp lib/player/player.cpp  lib/HUD/hud.cpp lib/display/display.cpp lib/sprites/sprite.cpp lib/maps/maps.cpp lib/maps/assets.cpp lib/gamemode/gamemode.cpp lib/jeu/jeu.cpp lib/menu/menu.cpp lib/pause/pauses.cpp lib/button/button.cpp lib/donjon/donjon.cpp lib/donjon/tree.cpp lib/Cartes/cartes.cpp lib/utility/utility.cpp lib/Cartes/tile.cpp lib/weapon/armes.cpp lib/entity/entity.cpp lib/monster/monster.cpp)

add_executable(mon_programme ${SRCS})

add_dependencies(mon_programme clean_tmxlite)

target_include_directories(mon_programme PUBLIC ${SOURCE_DIR}/tmxlite/include )

# Link SDL2, SDL2_ttf, SDL2_mixer, and tmxlite to your target
target_link_libraries(mon_programme 
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    ${CMAKE_BINARY_DIR}/third-party/src/tmxlite/tmxlite/build/libtmxlite.so
)

add_dependencies(mon_programme build_tmxlite)
