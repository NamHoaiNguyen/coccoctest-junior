#include "algo.h"

using namespace std;

void Algo::handleRequest() {
    initialize();
    execute();
}

void Algo::initialize() {
    for (const auto& elem : _parser->_setCommands) {
        if (elem == "dimension") {
            _setCommand[elem] = std::make_shared<Dimension>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        } else if (elem == "line_to") {
            _setCommand[elem] = std::make_shared<Line>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        } else if (elem == "move_to") {
            _setCommand[elem] = std::make_shared<Move>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        }
    }
}

void Algo::execute() {
    /*
        Handle case when first command is line_to
    */
    int index = 0;
    int indexLine = 0;

    for (auto elem : _parser->_info) {
        if (elem.command == "dimension") {
            auto dimensionHandle = _setCommand.find(elem.command);

            assert(dimensionHandle != _setCommand.end());

            if (dimensionHandle != _setCommand.end()) {
                dimensionHandle->second->handle(elem);
            }
        } else if (elem.command == "line_to") {
            if (index == 1 && indexLine == 0) {
                this->_prevData.command = "line_to";
                _prevData.axis.first = "0";
                _prevData.axis.second = "0";
                indexLine++;
            }

            auto lineHandle = _setCommand.find(elem.command);

            assert(lineHandle != _setCommand.end());

            if (lineHandle != _setCommand.end()) {
                lineHandle->second->handle(elem);
            }
        } else if (elem.command == "move_to") {
            auto moveHandle = _setCommand.find(elem.command);

            assert(moveHandle != _setCommand.end());

            if (moveHandle != _setCommand.end()) {
                moveHandle->second->handle(elem);
            }
        }

        if (elem.command != "dimension") {
            _prevData = elem;
        }
        getPrevData();
        index++;
    }

    setInfoForRender();
    preprocessData();
}

void Algo::preprocessData() {
    /*
        Remove duplicates axis
        Sort data based on axis
        Then erase all duplicates axis.
    */
    std::sort(_result.begin(), _result.end(), [](const auto& a, const auto& b){
        if (a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    });

    _result.erase(std::unique(_result.begin(), _result.end(), [](const auto& a, const auto& b){
        return a.x == b.x &&  a.y == b.y;
    }), _result.end());
}

void Algo::setInfoForRender() {
    auto dimensionHandle  = _setCommand.find("dimension");
    auto lineHandle = _setCommand.find("line_to");

    assert(dimensionHandle != _setCommand.end());
    assert(lineHandle != _setCommand.end());

    this->_result = lineHandle->second->getAxis();
    this->_dimen = dimensionHandle->second->getDimension();
}

DataCommand Algo::getPrevData() {
    return this->_prevData;
}

DimensionAlgo Algo::getDimension() {
    return this->_dimen;
}

std::vector<AxisAlgo>& Algo::getAxisAlgo() {
    return this->_result;
}