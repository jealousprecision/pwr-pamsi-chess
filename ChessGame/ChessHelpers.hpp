#pragma once

#include <vector>
#include <ChessGame/GameState.hpp>
#include <ChessGame/Player.hpp>

int evalGameState(const ChessGameState& source, Ownership player);

int getPieceValue(PieceType piece);

std::vector<ChessGameState::MoveType> getPossibleMovesForPiece(
        const ChessGameState& source,
        unsigned col,
        unsigned row);

std::vector<ChessGameState::MoveType> getAllPossibleMovesForPlayer(
        const ChessGameState& source,
        PlayerColor player);
