#ifndef COMMAND_H
#define COMMAND_H

#include "../common/command_data.h"

#include <memory>

class Algo;

class Command {
    public:
        virtual void handle(const Data& data) = 0;

        virtual void addAlgo(std::weak_ptr<Algo> algo) = 0;
};

#endif