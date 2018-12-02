#pragma once

#include <iostream>

namespace log {

inline void error(const char* location, const char* message)
{
    std::cout << "[ERROR] (" << location << ") " << message << std::endl;
}

} // namespace log
