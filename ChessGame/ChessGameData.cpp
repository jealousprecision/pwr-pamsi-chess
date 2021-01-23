#include "ChessGameData.hpp"

#include <tuple>
#include <sstream>

namespace
{

void initBaseRow(ChessGameData& state, unsigned row, Ownership owner, bool queenFirst = true)
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

void initSecondRow(ChessGameData& state, unsigned row, Ownership owner)
{
    auto& b = state.matrix;
    for (unsigned col = 0; col < 8; ++col)
    {
        b[col][row] = Field{owner, PieceType::Pawn};
    }
}

}  // namespace

ChessGameData::ChessGameData() :
    matrix(8, std::vector<Field>(8))
{
    initBaseRow(*this, 0, Ownership::White);
    initSecondRow(*this, 1, Ownership::White);

    initBaseRow(*this, 7, Ownership::Black, false);
    initSecondRow(*this, 6, Ownership::Black);
}

void ChessGameData::apply(Move move)
{
    matrix[move.colTo][move.rowTo] = matrix[move.colFrom][move.rowFrom];
    matrix[move.colFrom][move.rowFrom] = Field();
}

std::ostream& operator<<(std::ostream& os, const Move& obj)
{
    constexpr char dictionary[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    return os << dictionary[obj.colFrom] << obj.rowFrom + 1 << " => "
        << dictionary[obj.colTo] << obj.rowTo + 1;
}

std::string toString(const Move& obj)
{
    std::stringstream ssr;
    ssr << obj;
    return ssr.str();
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
        throw std::runtime_error("negate(): Ownership value not found");
    }
}

bool operator==(Move lhs, Move rhs)
{
    return std::tie(lhs.colFrom, lhs.rowFrom, lhs.colTo, lhs.rowTo)
        == std::tie(rhs.colFrom, rhs.rowFrom, rhs.colTo, rhs.rowTo);
}

