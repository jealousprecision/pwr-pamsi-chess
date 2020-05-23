#pragma once

class IChessGameState
{
public:
    virtual void update() = 0;

    virtual void onInit() {}
    virtual void onExit() {}
};
