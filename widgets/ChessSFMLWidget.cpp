#include "ChessSFMLWidget.hpp"

#include <iostream>
#include <QMouseEvent>

ChessSFMLWidget::ChessSFMLWidget(QWidget* parent, const QPoint& pos, const QSize& size, ChessGame& game) :
    QSFMLCanvas(parent, pos, size, 1),
    game_(game)
{}

void ChessSFMLWidget::OnInit()
{
    boardTxt.loadFromFile("./board_new360.png");
    boardSpr.setTexture(boardTxt);

    piecesTxt.loadFromFile("./pieces.png");

    constexpr auto pieceSize = 6u;
    PieceType pieces[pieceSize]{PieceType::King, PieceType::Queen, PieceType::Bishop, PieceType::Knight, PieceType::Rook, PieceType::Pawn};

    for (unsigned i = 0; i < pieceSize; ++i)
    {
        sf::Rect<int> rect(i * 45, 0, 45, 45);
        pieceWhiteToSpriteMap[pieces[i]] = sf::Sprite(piecesTxt, rect);
    }

    for (unsigned i = 0; i < pieceSize; ++i)
    {
        sf::Rect<int> rect(i * 45, 45, 45, 45);
        pieceBlackToSpriteMap[pieces[i]] = sf::Sprite(piecesTxt, rect);
    }
}

void ChessSFMLWidget::OnUpdate()
{
    clear(sf::Color(255, 255, 255));
    draw(boardSpr);

    auto& state = game_.getState().matrix;

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
}

void ChessSFMLWidget::mousePressEvent(QMouseEvent *event)
{
    constexpr auto REC_SIDE = 45;
    std::cout << "mouse pressed" << std::endl;

    if (event->button() != Qt::MouseButton::LeftButton)
        return;

    unsigned col = event->x() / REC_SIDE;
    unsigned row = event->y() / REC_SIDE;

    game_.playerMoveSlot(ChessGameState::MoveType{col, row, col, row - 1});
}


