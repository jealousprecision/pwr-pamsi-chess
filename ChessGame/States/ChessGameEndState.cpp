#include "ChessGameEndState.hpp"

#include <stdexcept>

bool ChessGameEndState::applyMove(const Move&)
{
    return false;
}

const BoardPositionToPossibleMovesMap& ChessGameEndState::getPossibleMoves() const
{
    throw std::runtime_error("ChessGameEndState::getPossibleMoves(): no moves for ended game");
}
