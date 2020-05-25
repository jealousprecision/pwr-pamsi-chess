#include "ChessGameCheckState.hpp"

#include <algorithm>
#include <stdexcept>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

void ChessGameCheckState::update()
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

        // if player still checked after move,
        // now end the game, in future just do nothing
        if (isPlayerInCheck(game_.gameState, game_.currentPlayerColor))
        {
            game_.getPlayer(game_.currentPlayerColor).gameEndedSlot(false);
            game_.getPlayer(negate(game_.currentPlayerColor)).gameEndedSlot(true);

            game_.stateMachine.changeState(ChessGameStateMachine::State::End);
        }
        else
        {
            game_.currentPlayerColor = negate(game_.currentPlayerColor);
        }
    }
}

std::vector<ChessGameState::MoveType> ChessGameCheckState::getPossibleMoves() const
{
    throw std::runtime_error("not implemented");
}
