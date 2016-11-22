add_library(SharedLib 
    Game.cpp
    Game.h
    headers.h
    Player.cpp
    Player.h
    sockets.cpp
    sockets.h)
target_link_libraries(SharedLib pthread ${SFML_LIBRARIES})
