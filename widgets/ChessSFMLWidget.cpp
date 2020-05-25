#include "ChessSFMLWidget.hpp"

#include <iostream>
#include <stdexcept>

#include <QMouseEvent>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

namespace
{

bool inBounds(unsigned col, unsigned row)
{
    return col < 8 && row < 8;
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
        std::cout << "mouse pressed" << std::endl;

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
            moves = getPossibleMovesForPiece(game_.gameState, col, row);
        }
        else
        {
            moves.clear();
        }
    }
}

void ChessSFMLWidget::yourTurnSlot()
{
    std::cout << "ChessSFMLWidget::yourTurnSlot()" << std::endl;

    myTurn = true;
}

void ChessSFMLWidget::gameEndedSlot(bool won)
{
    throw std::runtime_error("ChessSFMLWidget::gameEndedSlot(): not implemented");
}
