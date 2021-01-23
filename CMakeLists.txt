cmake_minimum_required(VERSION 3.5)

project(pwr-pamsi-chess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(pwr-pamsi-chess
    main.cpp    
    ChessGame/BoardPositionToPossibleMovesMap.cpp
    ChessGame/ChessGameData.cpp
    ChessGame/ChessGame.cpp
    ChessGame/ChessHelpers.cpp
    ChessGame/Enums.cpp
    ChessGame/Player.cpp
    ChessGame/DummyPlayer.cpp
    ChessGame/PlayerAi.cpp
    ChessGame/States/ChessGameStateMachine.cpp
    ChessGame/States/ChessGameEndState.cpp
    ChessGame/States/ChessGameDefaultState.cpp
    ChessGame/States/ChessGameCheckState.cpp
    widgets/QSFMLWidget.cpp
    widgets/ChessSFMLWidget.cpp
)

target_link_libraries(pwr-pamsi-chess PRIVATE Qt5::Widgets sfml-graphics sfml-audio)
