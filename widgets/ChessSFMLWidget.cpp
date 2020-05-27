#include "ChessSFMLWidget.hpp"

#include <iostream>
#include <stdexcept>

#include <QMouseEvent>
#include <QInputDialog>
#include <QStringList>
#include <QMessageBox>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

namespace
{

bool inBounds(unsigned col, unsigned row)
{
    return col < 8 && row < 8;
}

PieceType translateToPieceType(const QString& string)
{
    if (string == "Rook")
        return PieceType::Rook;

    if (string == "Knight")
        return PieceType::Knight;

    if (string == "Bishop")
        return PieceType::Bishop;

    if (string == "Queen")
        return PieceType::Queen;

    throw std::runtime_error("translateToPieceType(): not valid string");
}

}  // namespace

ChessSFMLWidget::ChessSFMLWidget(
    QWidget* parent,
    const QPoint& pos,
    const QSize& size,
    ChessGame& game,
    PlayerColor color) :
        QSFMLCanvas(parent, pos, size, 1),
        Player(game, color)
{}

void ChessSFMLWidget::OnInit()
{
    spritesheet.loadFromFile("./graphics/spritesheet.png");
    sf::Rect<int> mainBoard(0, 0, 360, 360);
    boardSpr.setTexture(spritesheet);
    boardSpr.setTextureRect(mainBoard);

    constexpr auto pieceSize = 6u;
    PieceType pieces[pieceSize]{PieceType::King, PieceType::Queen, PieceType::Bishop, PieceType::Knight, PieceType::Rook, PieceType::Pawn};

    for (unsigned i = 0; i < pieceSize; ++i)
    {
        sf::Rect<int> rect(i * 45, 360, 45, 45);
        pieceWhiteToSpriteMap[pieces[i]] = sf::Sprite(spritesheet, rect);
    }

    for (unsigned i = 0; i < pieceSize; ++i)
    {
        sf::Rect<int> rect(i * 45, 45 + 360, 45, 45);
        pieceBlackToSpriteMap[pieces[i]] = sf::Sprite(spritesheet, rect);
    }

    //markedTxt.loadFromFile("./graphics/marked.png");
    markedSpr.setTexture(spritesheet);
    sf::Rect<int> markedRect(0, 360 + 2 * 45, 45, 45);
    markedSpr.setTextureRect(markedRect);
}

void ChessSFMLWidget::OnUpdate()
{
    clear(sf::Color(255, 255, 255));
    draw(boardSpr);

    auto& state = game_.gameState.matrix;

    constexpr auto REC_SIDE = 45u;
    for (unsigned col = 0; col < state.size(); ++col)
    {
        for (unsigned row = 0; row < state[0].size(); ++row)
        {
            sf::Transform transform;
            transform.translate(col * REC_SIDE, row * REC_SIDE);
            sf::RenderStates renderState(transform);

            if (state[col][row].owner == Ownership::White)
            {
                draw(pieceWhiteToSpriteMap[state[col][row].piece], renderState);
            }
            else if (state[col][row].owner == Ownership::Black)
            {
                draw(pieceBlackToSpriteMap[state[col][row].piece], renderState);
            }
        }
    }

    for (auto move : moves)
    {
        auto col = move.colTo, row = move.rowTo;
        sf::Transform transform;
        transform.translate(col * REC_SIDE, row * REC_SIDE);
        sf::RenderStates renderState(transform);

        draw(markedSpr, renderState);
    }
}

void ChessSFMLWidget::mousePressEvent(QMouseEvent *event)
{
    constexpr auto REC_SIDE = 45;

    if (event->button() == Qt::MouseButton::LeftButton && myTurn)
    {
        unsigned col = event->x() / REC_SIDE;
        unsigned row = event->y() / REC_SIDE;

        if (!moves.empty())
        {
            auto found = std::find_if(moves.begin(), moves.end(),
                [&](const auto& move)
                {
                    return move.colTo == col && move.rowTo == row;
                });

            if (found != moves.end())
            {
                game_.playerMoveSlot(*this, *found);
                myTurn = false;
                moves.clear();
                return;
            }
        }

        if (inBounds(col, row) && game_.gameState.matrix[col][row].owner == toOwnership(color_))
        {
            const auto& movesMap = game_.stateMachine.getCurrentState().getPossibleMoves();
            BoardPosition pos{col, row};
            if (movesMap.count(pos))
                moves = movesMap.at(pos);
            else
                moves.clear();
        }
        else
        {
            moves.clear();
        }
    }
}

void ChessSFMLWidget::yourTurnSlot()
{
    myTurn = true;
}

void ChessSFMLWidget::gameEndedSlot(bool won)
{
    QMessageBox msg(QMessageBox::Icon::NoIcon, "", won ? "You won!" : "You lose");
    msg.exec();
}

PieceType ChessSFMLWidget::promotionSlot()
{
    QStringList items;
    items << "Rook" << "Knight" << "Knight" << "Bishop" << "Queen";
    bool ok = false;
    QString result;

    while (!ok)
    {
        result = QInputDialog::getItem(this, "Promotion!", "Piece:", items, 0, false, &ok);
    }

    return translateToPieceType(result);
}
