#include "DummyPlayer.hpp"

#include <cstdlib>
#include <iostream>
#include <ChessGame/ChessGameData.hpp>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

namespace
{

ChessGameData::MoveType getRandomMove(const BoardPositionToPossibleMovesMap& map)
{
    const auto& vec = std::next(map.begin(), std::rand() % map.size())->second;
    return vec[std::rand() % vec.size()];
}

}  // namespace

void DummyPlayer::update()
{
    if (yourTurn_ && isPlaying)
    {
        yourTurn_ = false;
        //std::cout << "DummyPlayer(" << toString(color_) << "): ";

        //ChessGameState::MoveType move;
        //std::cin >> move.colFrom >> move.rowFrom >> move.colTo >> move.rowTo;

        auto move = getRandomMove(game_.stateMachine.getCurrentState().getPossibleMoves());

        std::cout << "DummyPlayer(" << toString(color_) << "): " << move << std::endl;

        game_.playerMoveCallback(*this, move);
    }
}

void DummyPlayer::yourTurnCallback()
{
    yourTurn_ = true;
}

PieceType DummyPlayer::promotionResponse()
{
    constexpr PieceType pieces[4]{PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen};
    return pieces[std::rand() % 4];
}

void DummyPlayer::gameEndedCallback(bool won)
{
    isPlaying = false;
}


