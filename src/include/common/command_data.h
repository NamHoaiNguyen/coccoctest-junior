#ifndef COMMAND_DATA_H
#define COMMAND_DATA_H

#include<string>

struct DataCommand {
    std::string command;
    std::pair<std::string, std::string> axis;
};

struct AxisAlgo {
    int x;
    int y;
};

struct DimensionAlgo {
    int dimension;
};

#endif