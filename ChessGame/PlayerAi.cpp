#include "PlayerAi.hpp"

#include <iostream>
#include <MinMax.hpp>
#include <ChessGame/ChessGame.hpp>

PlayerAi::PlayerAi(ChessGame& game, PlayerColor color) :
    Player(game, color)
{}

void PlayerAi::yourTurnCallback()
{
    constexpr auto DIFFICULTY = 2u;

    auto move = MinMax::getOptimalMove(game_, color_, DIFFICULTY);
    game_.playerMoveCallback(move);

    std::cout << "PlayerAi(" << toString(color_) << "): " << move << std::endl;
}

void PlayerAi::gameEndedCallback(bool)
{
    isPlaying_ = false;
}

PieceType PlayerAi::promotionResponse()
{
    return PieceType::Queen;
}
