#include "ChessGameCheckState.hpp"

#include <algorithm>
#include <stdexcept>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessHelpers.hpp>

ChessGameCheckState::ChessGameCheckState(ChessGame& game)
    : game_(game)
{}

bool ChessGameCheckState::applyMove(const Move& move)
{
    applyMoveToChessGame(move, game_, possibleMoves_);

    if (isPlayerInCheck(game_.gameState, game_.currentPlayerColor))
    {
        possibleMoves_.clear();
        initPossibleMovesMap_();

        // player responded to check
        // by check-mating
        if (possibleMoves_.empty())
        {
            game_.playerThatWon = negate(game_.currentPlayerColor);
            game_.stateMachine.changeState(ChessGameStateMachine::State::End);
            return false;
        }
    }
    else
    {
        game_.stateMachine.changeState(ChessGameStateMachine::State::Default);
    }

    return true;
}

const BoardPositionToPossibleMovesMap& ChessGameCheckState::getPossibleMoves() const
{
    return possibleMoves_;
}

void ChessGameCheckState::onInit()
{
    initPossibleMovesMap_();

    if (possibleMoves_.empty())
    {
        // every possible move still results in check
        // game ends
        game_.playerThatWon = negate(game_.currentPlayerColor);
        game_.stateMachine.changeState(ChessGameStateMachine::State::End);
    }
}

void ChessGameCheckState::onExit()
{
    possibleMoves_.clear();
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
            possibleMoves_[getBoardPosition_From(move)].push_back(move);
        }
    }
}
