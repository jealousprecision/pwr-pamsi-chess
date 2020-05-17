#include "GameState.hpp"

namespace
{

void initBaseRow(std::vector<Field>& row, Ownership owner, bool queenFirst = true)
{
    row[0] = row[7] = Field{owner, PieceType::Rook};
    row[1] = row[6] = Field{owner, PieceType::Knight};
    row[2] = row[5] = Field{owner, PieceType::Bishop};

    auto queenCol = queenFirst ? 3 : 4;
    auto kingCol = queenFirst ? 4 : 3;

    row[queenCol] = Field{owner, PieceType::Queen};
    row[kingCol] = Field{owner, PieceType::King};
}

void initSecondRow(std::vector<Field>& row, Ownership owner)
{
    std::fill(row.begin(), row.end(), Field{owner, PieceType::Pawn});
}

}  // namespace

ChessGameState::ChessGameState() :
    state(8, std::vector<Field>(8))
{
    initBaseRow(state[0], Ownership::White);
    initSecondRow(state[1], Ownership::White);

    initBaseRow(state[7], Ownership::Black, false);
    initSecondRow(state[6], Ownership::Black);
}
