#include "ChessGameStatesHelpers.hpp"

#include <ChessGame/ChessHelpers.hpp>

bool isMoveEventValid(const ChessGame::MoveEvent& moveEvent, const ChessGame& game)
{
    if (moveEvent.player.getPlayerColor() != game.currentPlayerColor)
        return false;

    if (getOwnershipOfFieldFrom(game.gameState, moveEvent.moveType) != toOwnership(game.currentPlayerColor))
        return false;

    return true;
}

std::optional<BoardPosition> getPawnAtEnd(const ChessGameState& gameState, PlayerColor color)
{
    constexpr auto boardSize = 8u;

    if (color == PlayerColor::White)
    {
        for (unsigned col = 0; col < boardSize; ++col)
            if (gameState.matrix[col][7].piece == PieceType::Pawn)
                return BoardPosition{col, 7};
    }
    else
    {
        for (unsigned col = 0; col < boardSize; ++col)
            if (gameState.matrix[col][0].piece == PieceType::Pawn)
                return BoardPosition{col, 0};
    }

    return std::nullopt;
}
