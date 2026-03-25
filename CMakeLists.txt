# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.24)
project("td03")
# Trouve tous les fichiers .cpp dans mon répertoire src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# On souhaite placer l'exécutable dans un sous-dossier "bin" au lieu de le mettre dans le dossier build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# On indique que l'on souhaite faire un exécutable avec nos fichiers .cpp
add_executable(td03 ${SRC_FILES})
target_compile_features(td03 PRIVATE cxx_std_20)

# le dossier contenant les fichiers d'en-tête pour notre executable helloImac
target_include_directories(td03 PUBLIC "src/")

if (MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors)
endif()