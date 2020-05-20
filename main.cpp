#include <memory>

#include <QApplication>
#include <QFrame>
#include "widgets/ChessSFMLWidget.hpp"

#include "ChessBasicBrancher.hpp"
#include "MinMax.hpp"

#include "Observer/Observer.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChessGame game;

    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("MyWindowTitle");
    mainFrame->resize(400, 400);
    mainFrame->show();

    ChessSFMLWidget chessWidget(mainFrame, QPoint(20, 20), QSize(360, 360), game);
    chessWidget.show();

    return a.exec();
}
