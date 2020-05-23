#pragma once

#include <vector>
#include <ChessGame/ChessGameState.hpp>
#include <ChessGame/Enums.hpp>

std::vector<ChessGameState::MoveType> getPossibleMovesForPiece(
        const ChessGameState& source,
        unsigned col,
        unsigned row);

std::vector<ChessGameState::MoveType> getAllPossibleMovesForPlayer(
        const ChessGameState& source,
        PlayerColor player);
