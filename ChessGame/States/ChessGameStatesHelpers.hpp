#pragma once

#include <optional>
#include <ChessGame/ChessGame.hpp>

bool isMoveEventValid(const ChessGame::MoveEvent& moveEvent, const ChessGame& game);
std::optional<BoardPosition> getPawnAtEnd(const ChessGameState& gameState, PlayerColor color);
