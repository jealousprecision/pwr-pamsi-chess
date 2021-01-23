#include "ChessGameDefaultState.hpp"

#include <algorithm>
#include <optional>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

ChessGameDefaultState::ChessGameDefaultState(ChessGame& chessGame)
    : game_(chessGame)
{}

void ChessGameDefaultState::onInit()
{
    initPossibleMoves_();
}

bool ChessGameDefaultState::applyMove(const Move& move)
{   
    applyMoveToChessGame(move, game_, possibleMoves_);

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
    return true;
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
    {
        possibleMoves_[BoardPosition{move.colFrom, move.rowFrom}].push_back(move);
    }
}
