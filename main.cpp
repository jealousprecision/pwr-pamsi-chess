#include <cstdlib>
#include <ctime>
#include <memory>

#include <QApplication>
#include <QFrame>

#include "widgets/ChessSFMLWidget.hpp"

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/DummyPlayer.hpp>

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));
    QApplication a(argc, argv);

    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("MyWindowTitle");
    mainFrame->resize(400, 400);
    mainFrame->show();

    ChessGame game;

    ChessSFMLWidget chessWidget(mainFrame, QPoint(20, 20), QSize(360, 360), game, PlayerColor::Black);
    chessWidget.show();

    DummyPlayer white(game, PlayerColor::White);
    DummyPlayer black(game, PlayerColor::Black);

    QTimer timer;
    timer.callOnTimeout(
        [&]()
        {
            white.update();
            black.update();
            game.update();
        });

    game.registerPlayer(white);
    game.registerPlayer(chessWidget);

    game.start();
    timer.start();

    return a.exec();
}
