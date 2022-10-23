#ifndef DIMENSION_COMMAND_H
#define DIMENSION_COMMAND_H

#include "command.h"
 
#include <iostream>
#include <memory>
#include <vector>

class Dimension:  public Command {
    private:
        std::vector<std::vector<int>> _square;

        std::weak_ptr<Algo> _algo;
        
        int _size;

    public:
        Dimension() = default;

        explicit Dimension(int size) : _size{size} {

        }

        void handle(const Data& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        void setSize(const Data& data);
};

#endif