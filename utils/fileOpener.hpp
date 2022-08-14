#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

class FileOpener
{

public:
    template <typename T>
    static ErrorCode loadVector(std::vector<T> &outVector,
                                const std::string &filename,
                                const bool isColumn = true);

private:
    static ErrorCode transformValue(const std::string &value,
                                    std::string &result);
    static ErrorCode transformValue(const std::string &value, int &result);
    static ErrorCode transformValue(const std::string &value,
                                    unsigned long &result);
};