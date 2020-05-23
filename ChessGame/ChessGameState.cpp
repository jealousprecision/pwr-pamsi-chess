#include "ChessGameState.hpp"

namespace
{

void initBaseRow(ChessGameState& state, unsigned row, Ownership owner, bool queenFirst = true)
{
    auto& b = state.matrix;
    b[0][row] = b[7][row] = Field{owner, PieceType::Rook};
    b[1][row] = b[6][row] = Field{owner, PieceType::Knight};
    b[2][row] = b[5][row] = Field{owner, PieceType::Bishop};

    auto queenCol = queenFirst ? 3 : 4;
    auto kingCol = queenFirst ? 4 : 3;

    b[queenCol][row] = Field{owner, PieceType::Queen};
    b[kingCol][row] = Field{owner, PieceType::King};
}

void initSecondRow(ChessGameState& state, unsigned row, Ownership owner)
{
    auto& b = state.matrix;
    for (unsigned col = 0; col < 8; ++col)
        b[col][row] = Field{owner, PieceType::Pawn};
}

}  // namespace

ChessGameState::ChessGameState() :
    matrix(8, std::vector<Field>(8))
{
    initBaseRow(*this, 0, Ownership::White);
    initSecondRow(*this, 1, Ownership::White);

    initBaseRow(*this, 7, Ownership::Black, false);
    initSecondRow(*this, 6, Ownership::Black);
}

std::ostream& operator<<(std::ostream& os, const ChessGameState::MoveType& obj)
{
    constexpr char dictionary[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    return os << dictionary[obj.colFrom] << obj.rowFrom << " => "
        << dictionary[obj.colTo] << obj.rowTo;
}

Ownership negate(Ownership original)
{
    switch(original)
    {
    case Ownership::White:
        return Ownership::Black;
    case Ownership::Black:
        return Ownership::White;
    default:
        throw std::runtime_error("negate(): Ownership vlaue not found");
    }
}
