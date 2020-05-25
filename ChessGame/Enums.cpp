#include "Enums.hpp"

Ownership toOwnership(PlayerColor color)
{
    return color == PlayerColor::White ? Ownership::White : Ownership::Black;
}

PlayerColor negate(PlayerColor color)
{
    return color == PlayerColor::White ? PlayerColor::Black : PlayerColor::White;
}

std::string toString(PlayerColor color)
{
    return color == PlayerColor::White ? "White" : "Black";
}
