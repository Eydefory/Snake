cmake_minimum_required(VERSION 3.16)
project(SnakeGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# На большинстве систем (в т.ч. после `apt install libsfml-dev` /
# `brew install sfml`) find_package найдёт SFML 2.5+ автоматически.
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(SnakeGame
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Apple.cpp
    src/ResourceManager.cpp
    src/Settings.cpp
    src/Button.cpp
)

target_include_directories(SnakeGame PRIVATE src)
target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# После сборки копируем папку assets рядом с исполняемым файлом,
# чтобы ResourceManager мог найти assets/images, assets/fonts, assets/sounds
# по относительному пути.
add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SnakeGame>/assets
)
