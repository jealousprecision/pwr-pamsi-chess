#pragma once

#include <limits>
#include <functional>
#include <vector>

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/Enums.hpp>
#include <ChessGame/ChessHelpers.hpp>

struct MinMax
{
    enum class Mode
    {
        Minimizing,
        Maximizing
    };

    static Mode negate(Mode mode)
    {
        return mode == Mode::Maximizing ? Mode::Minimizing : Mode::Maximizing;
    }

    static ChessGameData::MoveType getOptimalMove(
        const ChessGame& game,
        PlayerColor color,
        unsigned depth)
    {
        int maxValue = std::numeric_limits<int>::min();
        std::vector<ChessGameData::MoveType> optimalMoves;

        const auto& movesMap = game.stateMachine.getCurrentState().getPossibleMoves();

        for (const auto& [startPos, moves] : movesMap)
        {
            for (auto move : moves)
            {
                auto stateCopy = game.gameState;
                stateCopy.apply(move);

                // already done 1st move, now it opponents turn
                auto eval = getValueOfDepth(
                    stateCopy,
                    ::negate(game.currentPlayerColor),
                    game.currentPlayerColor,
                    Mode::Minimizing,
                    depth);

                if (eval > maxValue)
                {
                    maxValue = eval;
                    optimalMoves.clear();
                    optimalMoves.push_back(move);
                }
                else if (eval == maxValue)
                {
                    optimalMoves.push_back(move);
                }
            }
        }

        if (optimalMoves.size() == 0)
            throw std::runtime_error("MinMax::getOptimalMove(): no moves found?");

        return optimalMoves[std::rand() % optimalMoves.size()];
    }

    static int getValueOfDepth(
        const ChessGameData& state,
        PlayerColor currentPlayerColor,
        PlayerColor originalPlayer,
        Mode mode,
        unsigned depth)
    {
        if (depth == 0)
            return evalGameState(state, originalPlayer);

        std::function<bool(int, int)> cmp;
        int maxValue;
        if (mode == Mode::Maximizing)
        {
            cmp = std::less<int>();
            maxValue = std::numeric_limits<int>::min();
        }
        else
        {
            cmp = std::greater<int>();
            maxValue = std::numeric_limits<int>::max();
        }

        auto moves = getAllPossibleMovesForPlayer(state, currentPlayerColor);
        filterOutMovesThatResultInCheck(state, moves, currentPlayerColor);

        for (auto move : moves)
        {
            auto stateCopy = state;
            stateCopy.apply(move);

            auto eval = getValueOfDepth(
                stateCopy,
                ::negate(currentPlayerColor),
                originalPlayer,
                negate(mode),
                depth - 1);

            if (cmp(maxValue, eval))
                maxValue = eval;
        }

        return maxValue;
    }
};
