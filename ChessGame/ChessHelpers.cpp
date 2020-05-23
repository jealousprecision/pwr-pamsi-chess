#include "ChessHelpers.hpp"

#include <vector>
#include <ChessGame/ChessGameState.hpp>

namespace
{

using MoveType = ChessGameState::MoveType;

bool inBounds(int col, int row)
{
    return (0 <= col && col < 8) && (0 <= row && row < 8);
}

void downRight(int& c, int& r) {c++, r++;}
void downLeft(int& c, int& r) {c--, r++;}
void upRight(int& c, int& r) {c++, r--;}
void upLeft(int& c, int& r) {c--, r--;}

void addDiagonalMovements(std::vector<MoveType>& movements, const ChessGameState& source, unsigned col, unsigned row)
{
    auto player = source.matrix[col][row].owner;

    for (auto deltaFunc : {downRight, downLeft, upRight, upLeft})
    {
        int c = col, r = row;

        deltaFunc(c, r);
        for (; inBounds(c, r); deltaFunc(c, r))
        {
            if (source.matrix[c][r].owner == player)
                break;
            movements.push_back(MoveType{col, row, static_cast<unsigned>(c), static_cast<unsigned>(r)});
            if (source.matrix[c][r].owner != Ownership::None)
                break;
        }
    }
}

void down(int& c, int& r) { r++; }
void up(int& c, int& r) { r--; }
void left(int& c, int& r) { c--; }
void right(int& c, int& r) { c++; }

void addLineMovements(std::vector<MoveType>& movements, const ChessGameState& source, unsigned col, unsigned row)
{
    auto player = source.matrix[col][row].owner;
    for (auto deltaFunc : {down, up, left, right})
    {
        int c = col, r = row;

        deltaFunc(c, r);
        for (; inBounds(c, r); deltaFunc(c, r))
        {
            if (source.matrix[c][r].owner == player)
                break;
            movements.push_back(MoveType{col, row, static_cast<unsigned>(c), static_cast<unsigned>(r)});
            if (source.matrix[c][r].owner != Ownership::None)
                break;
        }
    }
}

std::vector<void(*)(int&, int&)> getDiagonalFncLst(void (*func)(int&, int&))
{
    if (func == &down || func == &up)
        return {&left, &right};
    else
        return {&down, &up};
}

void addKnightMovements(std::vector<MoveType>& movements, const ChessGameState& source, unsigned col, unsigned row)
{
    auto player = source.matrix[col][row].owner;

    for (auto& firstDelta : {down, up, left, right})
    {
        int c = col, r = row;

        firstDelta(c, r);
        firstDelta(c, r);

        if (!inBounds(c, r))
            continue;

        for (auto& secondDelta : getDiagonalFncLst(firstDelta))
        {
            int c2 = c, r2 = r;
            secondDelta(c2, r2);

            if (!inBounds(c2, r2))
                continue;

            if (source.matrix[c2][r2].owner == player)
                continue;

            movements.push_back(MoveType{col, row, static_cast<unsigned>(c2), static_cast<unsigned>(r2)});
        }
    }
}

void addPawnMovements(std::vector<MoveType>& movements, const ChessGameState& source, unsigned col, unsigned row)
{
    int delta = source.matrix[col][row].owner == Ownership::White ? 1 : -1;

    if (inBounds(col, row + delta) && source.matrix[col][row + delta].owner == Ownership::None)
        movements.push_back(MoveType{col, row, col, row + delta});

    if (inBounds(col + 1, row + delta) && source.matrix[col + 1][row + delta].owner != Ownership::None)
        movements.push_back(MoveType{col, row, col + 1, row + delta});

    if (inBounds(col - 1, row + delta) && source.matrix[col - 1][row + delta].owner != Ownership::None)
        movements.push_back(MoveType{col, row, col - 1, row + delta});
}

void addKingMovements(std::vector<MoveType>& movements, const ChessGameState& source, unsigned col, unsigned row)
{
    auto player = source.matrix[col][row].owner;

    for (int c_delta = -1; c_delta <= 1; ++c_delta)
    {
        for (int r_delta = -1; r_delta <= 1; ++r_delta)
        {
            if (r_delta == 0 && c_delta == 0)
                continue;

            if (!inBounds(col + c_delta, row + r_delta))
                continue;

            if (source.matrix[col + c_delta][row + r_delta].owner == player)
                continue;

            movements.push_back(MoveType{col, row, col + c_delta, row + r_delta});
        }
    }
}

}  // namespace

std::vector<ChessGameState::MoveType> getPossibleMovesForPiece(
        const ChessGameState& source,
        unsigned col,
        unsigned row)
{
    std::vector<MoveType> result;

    switch(source.matrix[col][row].piece)
    {
    case PieceType::Pawn:
        addPawnMovements(result, source, col, row);
        break;
    case PieceType::Rook:
        addLineMovements(result, source, col, row);
        break;
    case PieceType::Knight:
        addKnightMovements(result, source, col, row);
        break;
    case PieceType::Bishop:
        addDiagonalMovements(result, source, col, row);
        break;
    case PieceType::Queen:
        addDiagonalMovements(result, source, col, row);
        addLineMovements(result, source, col, row);
        break;
    case PieceType::King:
        addKingMovements(result, source, col, row);
        break;
    default:
        throw std::runtime_error("getPossibleMovesForPiece(): bad enum value");
    }

    return result;
}

std::vector<ChessGameState::MoveType> getAllPossibleMovesForPlayer(
        const ChessGameState& source,
        PlayerColor player)
{
    std::vector<ChessGameState::MoveType> result;
    auto playerOwnerhip = toOwnership(player);

    for (unsigned col = 0; col < source.matrix.size(); ++col)
    {
        for (unsigned row = 0; row < source.matrix.size(); ++col)
        {
            if (source.matrix[col][row].owner == playerOwnerhip)
            {
                auto movesForPiece = getPossibleMovesForPiece(source, col, row);
                std::move(movesForPiece.begin(), movesForPiece.end(), std::back_inserter(result));
            }
        }
    }

    return result;
}
