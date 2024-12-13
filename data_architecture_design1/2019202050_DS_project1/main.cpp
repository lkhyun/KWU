#include <iostream>
#include "manager.h"

int main(int argc, char* argv[])
{
    const char* commandFilepath = "command.txt"; //command.txt file route
    if (argc > 1)
        commandFilepath = argv[1];
        
    Manager m;
    m.Run(commandFilepath); 

    return 0;
}