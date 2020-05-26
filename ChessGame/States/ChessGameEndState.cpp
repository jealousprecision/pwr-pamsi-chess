#include "ChessGameEndState.hpp"

#include <stdexcept>

void ChessGameEndState::update()
{

}

const BoardPositionToPossibleMovesMap& ChessGameEndState::getPossibleMoves() const
{
    throw std::runtime_error("ChessGameEndState::getPossibleMoves(): no moves for ended game");
}
