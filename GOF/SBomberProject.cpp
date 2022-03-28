
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"
#include "FileLoggerSingletone.h"
//#include "ProxyLogger.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    InterfaceFileLogger* proxy(&(FileLoggerSingletone::getInstance()));
    proxy->OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    proxy->CloseLogFile();

    return 0;
}
