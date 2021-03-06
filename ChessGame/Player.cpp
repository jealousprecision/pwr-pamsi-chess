#include "Player.hpp"

Player::Player(ChessGame& game, PlayerColor color) :
    game_(game), color_(color)
{}

PlayerColor Player::getPlayerColor() const
{
    return color_;
}
