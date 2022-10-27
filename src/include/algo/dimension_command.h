#ifndef DIMENSION_COMMAND_H
#define DIMENSION_COMMAND_H

#include "command.h"
 
#include <iostream>
#include <memory>
#include <vector>

class Dimension:  public Command {
    private:
        std::vector<std::vector<int>> _square;

        /*Store data returned for Algo*/
        std::weak_ptr<Algo> _algo;
        
        int _size;

        DimensionAlgo _dimensionAlgo;

    public:
        Dimension() = default;

        explicit Dimension(int size) : _size{size} {

        }

        void handle(const DataCommand& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        std::vector<AxisAlgo> getAxis() override; 

        DimensionAlgo getDimension() override; 
        
        void setSize(const DataCommand& data);
};

#endif