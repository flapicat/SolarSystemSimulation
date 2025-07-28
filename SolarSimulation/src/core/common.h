#pragma once
#include <iostream>

#define ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: (" << #condition << "), " \
                  << "function " << __FUNCTION__ \
                  << ", file " << __FILE__ \
                  << ", line " << __LINE__ << "." << std::endl; \
        std::cerr << "Message: " << message << std::endl; \
        std::abort(); \
    } \

		