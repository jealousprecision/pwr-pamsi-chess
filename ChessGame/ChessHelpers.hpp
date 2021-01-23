#pragma once

#include <optional>
#include <vector>
#include <ChessGame/Enums.hpp>
#include <ChessGame/BoardPositionToPossibleMovesMap.hpp>

class Move;
class ChessGame;
class ChessGameData;

std::vector<Move> getPossibleMovesForPiece(
        const ChessGameData& source,
        unsigned col,
        unsigned row);

std::vector<Move> getAllPossibleMovesForPlayer(
        const ChessGameData& source,
        PlayerColor player);

Ownership getOwnershipOfFieldFrom(
        const ChessGameData& source,
        Move move);

bool isPlayerInCheck(
        const ChessGameData& source,
        PlayerColor player);

void filterOutMovesThatResultInCheck(
        const ChessGameData& gameState,
        std::vector<Move>& moves,
        PlayerColor color);

int evalGameState(const ChessGameData& source, PlayerColor color);
std::optional<BoardPosition> getPawnAtEnd(const ChessGameData& gameState, PlayerColor color);
void applyMoveToChessGame(const Move& move, ChessGame& chessGame, const BoardPositionToPossibleMovesMap& possibleMoves);
