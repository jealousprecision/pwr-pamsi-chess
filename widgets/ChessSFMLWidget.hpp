#pragma once

#include <map>

#include <widgets/QSFMLWidget.hpp>
#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameState.hpp>

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

    void yourTurnCallback() override;
    void gameEndedCallback(bool won) override;
    PieceType promotionResponse() override;

protected:
    // graphics oriented objects
    void OnInit() override;
    void OnUpdate() override;
    void mousePressEvent(QMouseEvent* event) override;

    sf::Texture spritesheet;

    sf::Sprite boardSpr;
    std::map<PieceType, sf::Sprite> pieceWhiteToSpriteMap;
    std::map<PieceType, sf::Sprite> pieceBlackToSpriteMap;
    sf::Sprite markedSpr;

    // player oriented objects
    std::vector<ChessGameState::MoveType> moves;
    bool myTurn = false;
};
