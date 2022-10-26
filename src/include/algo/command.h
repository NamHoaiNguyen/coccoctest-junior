#ifndef COMMAND_H
#define COMMAND_H

#include "../common/axis.h"
#include "../common/command_data.h"

#include <memory>
#include <vector>

class Algo;

class Command {
    public:
        virtual void handle(const DataCommand& data) = 0;

        virtual void addAlgo(std::weak_ptr<Algo> algo) = 0;

        virtual std::vector<AxisAlgo> getAxis() = 0; 

        virtual DimensionAlgo getDimension() = 0; 
};

#endif