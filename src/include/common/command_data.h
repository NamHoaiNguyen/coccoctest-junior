#ifndef COMMAND_DATA_H
#define COMMAND_DATA_H

#include<string>

struct Data {
    std::string command;
    std::pair<std::string, std::string> axis;
};

#endif