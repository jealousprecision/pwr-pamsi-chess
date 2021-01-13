#include "ChessGameDefaultState.hpp"

#include <algorithm>
#include <optional>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>
#include <ChessGame/States/ChessGameStatesHelpers.hpp>

void ChessGameDefaultState::onInit()
{
    initPossibleMoves_();
}

void ChessGameDefaultState::update()
{
    if (game_.moveEvent.has_value())
    {
        auto move = game_.moveEvent.value();
        game_.moveEvent.reset();

        if (!isMoveEventValid(move, game_))
            throw std::runtime_error("ChessGameDefaultState::update(): moveEvent not valid: " + toString(move.moveType));

        if (!possibleMoves_.count(getBoardPosition_From(move.moveType)))
            throw std::runtime_error("ChessGameDefaultState::update(): moveEvent not possible: " + toString(move.moveType));

        game_.gameState.apply(move.moveType);
        game_.lastMove = move.moveType;

        if (auto pawnAtEnd = getPawnAtEnd(game_.gameState, game_.currentPlayerColor))
        {
            auto piece = game_.getCurrentPlayer().promotionResponse();
            game_.gameState.matrix[pawnAtEnd->col][pawnAtEnd->row].piece = piece;
        }
        game_.currentPlayerColor = negate(game_.currentPlayerColor);

        // if next player is in check, change state
        if (isPlayerInCheck(game_.gameState, game_.currentPlayerColor))
        {
            game_.stateMachine.changeState(ChessGameStateMachine::State::Check);
        }
        else
        {
            // prepare for next's player moves
            possibleMoves_.clear();
            initPossibleMoves_();
        }

        game_.getCurrentPlayer().yourTurnCallback();
    }
}

void ChessGameDefaultState::onExit()
{
    possibleMoves_.clear();
}

const BoardPositionToPossibleMovesMap& ChessGameDefaultState::getPossibleMoves() const
{
    return possibleMoves_;
}

void ChessGameDefaultState::initPossibleMoves_()
{
    auto allMoves = getAllPossibleMovesForPlayer(game_.gameState, game_.currentPlayerColor);
    filterOutMovesThatResultInCheck(game_.gameState, allMoves, game_.currentPlayerColor);

    for (auto move : allMoves)
        possibleMoves_[BoardPosition{move.colFrom, move.rowFrom}].push_back(move);
}
