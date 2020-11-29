#include "Logger.h"


void Logger::setColor(tEnuColors color) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //std::cout << "/*WINDOWS*/" << std::endl;
    /*"WINDOWS"*/
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int code;
    switch (color) {
    case tEnuColors::RED:
        code = 4;
        break;
    case tEnuColors::GREEN:
        code = 2;
        break;
    default:
        code = 7;
        break;
    }
    SetConsoleTextAttribute(hConsole, code);

#elif __linux__

    /* "LINUX" */
    switch (color) {
    case tEnuColors::RED:
        std::cout << "\x1B[31m";
        break;
    case tEnuColors::GREEN:
        std::cout<<"\x1B[32m";
        break;
    default:
        std::cout<<"\033[0m";
        break;
    }

#else
#   error "Unknown compiler"
#endif
}

