#pragma once
#include <memory>

class SBomberImp;

class SBomber
{
public:

    SBomber();
    // ~SBomber();
    
    bool GetExitFlag() const;

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    std::shared_ptr<SBomberImp> impl;
    
};