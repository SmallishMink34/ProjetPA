cmake_minimum_required(VERSION 3.10)
project(mon_programme)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})


include(ExternalProject)

ExternalProject_Add(
    tmxlite
    PREFIX ${CMAKE_BINARY_DIR}/third-party
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG master
    UPDATE_DISCONNECTED TRUE
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    CONFIGURE_COMMAND ""  # Supprime la configuration du projet, car vous n'en avez pas besoin
    BUILD_COMMAND ""  # Supprime la phase de construction, car vous n'en avez pas besoin
    INSTALL_COMMAND ""  # Supprime la phase d'installation, car vous n'en avez pas besoin
    LOG_DOWNLOAD ON  # Active les journaux de téléchargement
)

# Obtenez le répertoire d'installation généré par ExternalProject_Add
ExternalProject_Get_Property(tmxlite SOURCE_DIR)


# Ajoutez une cible pour exécuter la commande de nettoyage après le téléchargement
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
set(SRCS main.cpp lib/world/world.cpp lib/player/player.cpp lib/display/display.cpp lib/sprites/sprite.cpp lib/maps/maps.cpp lib/maps/assets.cpp lib/jeu/jeu.cpp lib/menu/menu.cpp lib/pause/pauses.cpp lib/gamemode/gamemode.cpp  lib/button/button.cpp )

add_executable(mon_programme ${SRCS})

# Assurez-vous que la cible de nettoyage est exécutée lors de la construction
add_dependencies(mon_programme clean_tmxlite)


target_include_directories(mon_programme PUBLIC ${SOURCE_DIR}/tmxlite/include)
target_link_libraries(mon_programme ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${CMAKE_BINARY_DIR}/third-party/src/tmxlite/tmxlite/build/libtmxlite.so)

add_dependencies(mon_programme build_tmxlite)
