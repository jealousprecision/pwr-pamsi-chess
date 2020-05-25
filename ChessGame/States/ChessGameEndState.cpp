#include "ChessGameEndState.hpp"

#include <stdexcept>

void ChessGameEndState::update()
{

}

std::vector<ChessGameState::MoveType> ChessGameEndState::getPossibleMoves() const
{
    return {};
}
