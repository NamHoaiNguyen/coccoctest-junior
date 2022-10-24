#include "move_command.h"
#include "algo.h"

void Move::handle(const Data& data) {
    // std::cout << "move handle in algo folder" << std::endl;
    setUpParams(data);
} 

void Move::setUpParams(const Data& data) {
    // auto axis = std::make_pair<std::stoi(data.axis.first), std::stoi(data.axis.second)>;
    Axis axis;

    axis.axis_x = std::stoi(data.axis.first);
    axis.axis_y = std::stoi(data.axis.second);
    /*Care!!! Maybe segmant fault when adding reference to vector*/
    _historyMoves.push_back(data);
    _history.push_back(axis);


    Data prevData;

    if (auto subscriber = this->_algo.lock(); subscriber) {
        prevData = subscriber->getPrevData();
    }

    // std::cout << prevData.command << " " << prevData.axis.first << " " << prevData.axis.second << " " << __FILE__ << " " << __func__ << std::endl;

}

void Move::addAlgo(std::weak_ptr<Algo> algo) {
    this->_algo = algo;
}