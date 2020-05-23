#pragma once

#include <map>

#include <widgets/QSFMLWidget.hpp>
#include <ChessGame/Player.hpp>

class ChessGame;

class ChessSFMLWidget : public QSFMLCanvas, public Player
{
public:
    ChessSFMLWidget(
        QWidget* parent,
        const QPoint& pos,
        const QSize& size,
        ChessGame& game,
        PlayerColor color);

    void yourTurnSlot() override;
    void gameEndedSlot(bool won) override;

protected:
    void OnInit() override;
    void OnUpdate() override;
    void mousePressEvent(QMouseEvent* event) override;

    sf::Sprite boardSpr;
    sf::Texture boardTxt;

    sf::Texture piecesTxt;
    std::map<PieceType, sf::Sprite> pieceWhiteToSpriteMap;
    std::map<PieceType, sf::Sprite> pieceBlackToSpriteMap;
};
