#include "ChessGameDefaultState.hpp"

#include <ChessGame/ChessGame.hpp>

void ChessGameDefaultState::update()
{
    if (game_.moveEvent.has_value())
    {
        game_.moveEvent = std::nullopt;
        // check if move is legal
        // than apply move
        // than change current player
    }

    throw std::runtime_error("ChessGameDefaultState::update(): not implemented");
}
