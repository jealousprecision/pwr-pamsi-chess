#include "PlayerAi.hpp"

#include <iostream>
#include <MinMax.hpp>
#include <ChessGame/ChessGame.hpp>

PlayerAi::PlayerAi(ChessGame& game, PlayerColor color) :
    Player(game, color)
{}

void PlayerAi::yourTurnSlot()
{
    myTurn_ = true;
}

void PlayerAi::gameEndedSlot(bool)
{
    isPlaying_ = false;
}

PieceType PlayerAi::promotionSlot()
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
        game_.playerMoveSlot(*this, move);

        std::cout << "PlayerAi(" << toString(color_) << "): " << move << std::endl;
    }
}
