#include "ChessGameDefaultState.hpp"

#include <algorithm>
#include <optional>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

void ChessGameDefaultState::update()
{
    if (game_.moveEvent.has_value())
    {
        auto move = game_.moveEvent.value();
        game_.moveEvent.reset();

        if (move.player.getPlayerColor() != game_.currentPlayerColor)
            throw std::runtime_error("ChessGameDefaultState::update(): move by not current player!");

        if (getOwnershipOfFieldFrom(game_.gameState, move.moveType) != toOwnership(game_.currentPlayerColor))
            throw std::runtime_error("ChessGameDefaultState::update(): move by not current player!");

        auto everyMovePossible = getAllPossibleMovesForPlayer(game_.gameState, game_.currentPlayerColor);
        auto found = std::find(everyMovePossible.begin(), everyMovePossible.end(), move.moveType);

        if (found == everyMovePossible.end())
            throw std::runtime_error("ChessGameDefaultState::update(): move not possible!");

        game_.gameState.apply(move.moveType);
        game_.currentPlayerColor = negate(game_.currentPlayerColor);

        if (isPlayerInCheck(game_.gameState, game_.currentPlayerColor))
            game_.stateMachine.changeState(ChessGameStateMachine::State::Check);

        game_.getCurrentPlayer().yourTurnSlot();
    }
}

std::vector<ChessGameState::MoveType> ChessGameDefaultState::getPossibleMoves() const
{
    return getAllPossibleMovesForPlayer(game_.gameState, game_.currentPlayerColor);
}
