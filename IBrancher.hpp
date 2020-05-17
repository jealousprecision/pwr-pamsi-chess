#pragma once

#include <GraphList.hpp>

template<typename GameState>
class IBrancher
{
public:
    ~IBrancher() = default;

    virtual void branch(
            const GameState& source,
            GraphList<int, typename GameState::MoveType>& valueGraph) = 0;
};
