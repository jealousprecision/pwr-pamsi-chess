#include <memory>

#include <QApplication>
#include <QFrame>

#include "widgets/ChessSFMLWidget.hpp"

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/DummyPlayer.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("MyWindowTitle");
    mainFrame->resize(400, 400);
    mainFrame->show();

    ChessGame game;

    ChessSFMLWidget chessWidget(mainFrame, QPoint(20, 20), QSize(360, 360), game, PlayerColor::White);
    chessWidget.show();

    DummyPlayer black(game, PlayerColor::Black);

    game.registerPlayer(chessWidget);
    game.registerPlayer(black);

    game.start();

    return a.exec();
}
