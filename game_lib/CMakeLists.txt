add_library(game_lib
    board.cpp
    settings.cpp
    history.cpp
    game.cpp
)

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})