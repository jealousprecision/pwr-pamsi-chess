#include "PlayerAi.hpp"

#include <iostream>
#include <MinMax.hpp>
#include <ChessGame/ChessGame.hpp>

PlayerAi::PlayerAi(ChessGame& game, PlayerColor color) :
    Player(game, color)
{}

void PlayerAi::yourTurnCallback()
{
    myTurn_ = true;
}

void PlayerAi::gameEndedCallback(bool)
{
    isPlaying_ = false;
}

PieceType PlayerAi::promotionResponse()
{
    return PieceType::Queen;
}

void PlayerAi::update()
{
    constexpr auto DIFFICULTY = 2u;

    if (myTurn_ && isPlaying_)
    {
        myTurn_ = false;
        auto move = MinMax::getOptimalMove(game_, color_, DIFFICULTY);
        game_.playerMoveCallback(*this, move);

        std::cout << "PlayerAi(" << toString(color_) << "): " << move << std::endl;
    }
}
