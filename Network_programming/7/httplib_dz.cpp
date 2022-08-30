#include <iostream>
#include "ServerLib.h"

int main()
{
    ServerLib server;
    server.set_GET();
    server.listening();
    
    
    return 0;
}
