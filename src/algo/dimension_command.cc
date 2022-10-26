#include "dimension_command.h"

void Dimension::handle(const DataCommand& data) {
    // std::cout << "dimension handle in algo folder" << std::endl;
    setSize(data);
} 

void Dimension::setSize(const DataCommand& data) {
    this->_size = std::stoi(data.axis.first);
    // std::cout << this->_size << std::endl;
    _square.resize(this->_size, std::vector<int>(this->_size));

    this->_dimensionAlgo.dimension = this->_size;
}

void Dimension::addAlgo(std::weak_ptr<Algo> algo) {
    this->_algo = algo;
}

std::vector<AxisAlgo> Dimension::getAxis() {
    
}

DimensionAlgo Dimension::getDimension() {
    return this->_dimensionAlgo;
} 
