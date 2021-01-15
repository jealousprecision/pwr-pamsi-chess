#include <cstdlib>
#include <ctime>
#include <memory>

#include <QApplication>
#include <QFrame>

#include <widgets/ChessSFMLWidget.hpp>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/DummyPlayer.hpp>
#include <ChessGame/PlayerAi.hpp>

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));
    QApplication a(argc, argv);

    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("MyWindowTitle");
    mainFrame->resize(400, 400);
    mainFrame->show();

    ChessGame game;

    ChessSFMLWidget* chessWidget = new ChessSFMLWidget(mainFrame, QPoint(20, 20), QSize(360, 360), game, PlayerColor::Black);
    chessWidget->show();
    chessWidget->setParent(mainFrame);

    //PlayerAi playerAi(game, PlayerColor::White);
    DummyPlayer playerAi(game, PlayerColor::White);

    game.registerPlayer(playerAi);
    game.registerPlayer(*chessWidget);

    game.start();

    return a.exec();
}
