#include <string>
#include <iostream>

void printToConsole(const char* logLine) {
#if CMAKE_BUILD_TYPE == Debug
    std::cout << logLine << std::endl;
#endif
}

void printToConsole(std::string logLine) {
    printToConsole(logLine.c_str());
}