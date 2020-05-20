cmake_minimum_required(VERSION 3.5)

project(pwr-tic-tac LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# add sfml
set(SFML_DIR "~/lib/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(pwr-tic-tac
    main.cpp
    GraphList.hpp
    VoidType.hpp
    MinMax.cpp
    MinMax.hpp
    GameState.hpp
    GameState.cpp
    IBrancher.hpp
    ChessBasicBrancher.hpp
    ChessBasicBrancher.cpp
    ChessGame.hpp
    widgets/QSFMLWidget.cpp
    widgets/QSFMLWidget.hpp
    widgets/ChessSFMLWidget.cpp
    widgets/ChessSFMLWidget.hpp
    Observer/Observer.hpp
    Observer/Subject.hpp
)


target_link_libraries(pwr-tic-tac PRIVATE Qt5::Widgets sfml-graphics sfml-audio)
