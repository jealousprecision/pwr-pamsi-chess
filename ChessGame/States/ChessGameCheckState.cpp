#include "ChessGameCheckState.hpp"

#include <algorithm>
#include <stdexcept>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>
#include <ChessGame/States/ChessGameStatesHelpers.hpp>

void ChessGameCheckState::update()
{
    if (game_.moveEvent.has_value())
    {
        auto move = game_.moveEvent.value();
        game_.moveEvent.reset();

        if (!isMoveEventValid(move, game_))
            throw std::runtime_error("ChessGameDefaultState::update(): moveEvent not valid: " + toString(move.moveType));

        if (!possibleMovesMap_.count(getBoardPosition_From(move.moveType)))
            throw std::runtime_error("ChessGameDefaultState::update(): moveEvent not possible: " + toString(move.moveType));

        game_.gameState.apply(move.moveType);
        game_.lastMove = move.moveType;

        if (auto pawnAtEnd = getPawnAtEnd(game_.gameState, game_.currentPlayerColor))
        {
            auto piece = game_.getCurrentPlayer().promotionResponse();
            game_.gameState.matrix[pawnAtEnd->col][pawnAtEnd->row].piece = piece;
        }
        game_.currentPlayerColor = negate(game_.currentPlayerColor);

        // if enemy player is in check,
        if (isPlayerInCheck(game_.gameState, game_.currentPlayerColor))
        {
            possibleMovesMap_.clear();
            initPossibleMovesMap_();
        }
        else
        {
            game_.stateMachine.changeState(ChessGameStateMachine::State::Default);
            game_.getCurrentPlayer().yourTurnCallback();
        }
    }
}

const BoardPositionToPossibleMovesMap& ChessGameCheckState::getPossibleMoves() const
{
    return possibleMovesMap_;
}

void ChessGameCheckState::onInit()
{
    initPossibleMovesMap_();

    if (possibleMovesMap_.empty())
    {
        // every possible move still results in check
        // notify the players about match result
        game_.getCurrentPlayer().gameEndedCallback(false);
        game_.getPlayer(negate(game_.currentPlayerColor)).gameEndedCallback(true);
        game_.stateMachine.changeState(ChessGameStateMachine::State::End);
    }
}

void ChessGameCheckState::onExit()
{
    possibleMovesMap_.clear();
}

void ChessGameCheckState::initPossibleMovesMap_()
{
    auto moves = getAllPossibleMovesForPlayer(game_.gameState, game_.currentPlayerColor);

    for (auto move : moves)
    {
        auto stateCopy = game_.gameState;
        stateCopy.apply(move);

        // if check is avoided
        if (!isPlayerInCheck(stateCopy, game_.currentPlayerColor))
        {
            possibleMovesMap_[getBoardPosition_From(move)].push_back(move);
        }
    }
}
