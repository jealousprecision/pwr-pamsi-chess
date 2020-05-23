#include "Enums.hpp"

Ownership toOwnership(PlayerColor color)
{
    return color == PlayerColor::White ? Ownership::White : Ownership::Black;
}
