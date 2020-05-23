cmake_minimum_required(VERSION 3.5)

project(pwr-pamsi-chess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# add sfml
set(SFML_DIR "~/lib/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(Qt5_DIR "/home/adam/Qt/5.12.8/gcc_64/lib/cmake/Qt5/")
find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(pwr-pamsi-chess
    main.cpp
    #MinMax.cpp
    ChessGame/ChessGameState.cpp
    ChessGame/ChessBasicBrancher.cpp
    ChessGame/ChessGame.cpp
    ChessGame/ChessHelpers.cpp
    ChessGame/Player.cpp
    ChessGame/Enums.cpp
    ChessGame/States/ChessGameStateMachine.cpp
    ChessGame/States/ChessGameDefaultState.cpp
    ChessGame/States/ChessGameCheckState.cpp
    ChessGame/States/ChessGameEndState.cpp
    #ChessGame/PlayerAi.cpp
    widgets/QSFMLWidget.cpp
    widgets/ChessSFMLWidget.cpp
)


target_link_libraries(pwr-pamsi-chess PRIVATE Qt5::Widgets sfml-graphics sfml-audio)
