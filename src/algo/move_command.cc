#include "move_command.h"
#include "algo.h"

void Move::handle(const DataCommand& data) {
    setUpParams(data);
} 

void Move::setUpParams(const DataCommand& data) {
    AxisAlgo axis;

    axis.x = (data.axis.first);
    axis.y = (data.axis.second);
    _historyMoves.push_back(data);
    _history.push_back(axis);


    DataCommand prevData;

    if (auto subscriber = this->_algo.lock(); subscriber) {
        prevData = subscriber->getPrevData();
    }
}

std::vector<AxisAlgo> Move::getAxis() {
    return this->_history;
}

DimensionAlgo Move::getDimension() {
    
} 

void Move::addAlgo(std::weak_ptr<Algo> algo) {
    this->_algo = algo;
}