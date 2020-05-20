#include "QSFMLWidget.hpp"

#include <map>
#include <ChessGame.hpp>
#include <GameState.hpp>

class ChessSFMLWidget : public QSFMLCanvas
{
public:
    ChessSFMLWidget(QWidget* parent, const QPoint& pos, const QSize& size, ChessGame& game);

protected:
    void OnInit() override;
    void OnUpdate() override;
    void mousePressEvent(QMouseEvent* event) override;

    sf::Sprite boardSpr;
    sf::Texture boardTxt;

    sf::Texture piecesTxt;
    std::map<PieceType, sf::Sprite> pieceWhiteToSpriteMap;
    std::map<PieceType, sf::Sprite> pieceBlackToSpriteMap;

    ChessGame& game_;
};
