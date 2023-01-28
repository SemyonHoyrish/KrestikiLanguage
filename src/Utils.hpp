#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>


void LogInfo(std::string message)
{
    std::cout << "[INFO ] " << message << std::endl;
}

void LogWarning(std::string message)
{
    std::cout << "[WARN ] " << message << std::endl;
}

void LogError(std::string message)
{
    std::cout << "[ERROR] " << message << std::endl;
}

void LogFatal(std::string message)
{
    std::cout << "[FATAL] " << message << std::endl;
    exit(1);
}

#endif
