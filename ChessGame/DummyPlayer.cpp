#include "DummyPlayer.hpp"

#include <cstdlib>
#include <iostream>
#include <ChessGame/ChessGameState.hpp>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

void DummyPlayer::update()
{
    if (yourTurn_)
    {
        yourTurn_ = false;
        //std::cout << "DummyPlayer(" << toString(color_) << "): ";

        //ChessGameState::MoveType move;
        //std::cin >> move.colFrom >> move.rowFrom >> move.colTo >> move.rowTo;

        auto moves = game_.stateMachine.getCurrentState().getPossibleMoves();
        auto move = moves[std::rand() % moves.size()];

        std::cout << "DummyPlayer(" << toString(color_) << "): " << move << std::endl;

        game_.playerMoveSlot(*this, move);
    }
}

void DummyPlayer::yourTurnSlot()
{
    yourTurn_ = true;
}
