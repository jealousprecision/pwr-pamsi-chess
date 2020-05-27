#pragma once

#include <vector>
#include <ChessGame/ChessGameData.hpp>
#include <ChessGame/Enums.hpp>

std::vector<ChessGameData::MoveType> getPossibleMovesForPiece(
        const ChessGameData& source,
        unsigned col,
        unsigned row);

std::vector<ChessGameData::MoveType> getAllPossibleMovesForPlayer(
        const ChessGameData& source,
        PlayerColor player);

Ownership getOwnershipOfFieldFrom(
        const ChessGameData& source,
        ChessGameData::MoveType move);

bool isPlayerInCheck(
        const ChessGameData& source,
        PlayerColor player);

void filterOutMovesThatResultInCheck(
        const ChessGameData& gameState,
        std::vector<ChessGameData::MoveType>& moves,
        PlayerColor color);

int evalGameState(const ChessGameData& source, PlayerColor color);
