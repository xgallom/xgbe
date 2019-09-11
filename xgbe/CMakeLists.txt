find_library(libSDL2 SDL2)

set(files
        main.cpp
        Application.cpp
        KeyboardHandler.cpp
        Window.cpp
        )

add_executable(xgbe ${files})

target_link_libraries(xgbe emulation ${libSDL2})
