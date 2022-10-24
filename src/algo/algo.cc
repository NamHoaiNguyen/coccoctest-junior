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

    // testInit();
}

void Algo::execute() {
    /*
        Handle case when first command is line_to
    */
    int index = 0;
    int indexLine = 0;

    for (auto elem : _parser->_info) {
        // std::cout << index << std::endl;
        // std::cout << elem.command << " " <<  elem.axis.first << " " << elem.axis.second << " " << __FILE__ << " " << __func__  << " " << __LINE__ << std::endl;
        if (elem.command == "dimension") {
            // std::cout << "check execute dimension 1" << std::endl;
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
            // std::cout << "check execute move_to 1" << std::endl;

            auto moveHandle = _setCommand.find(elem.command);

            assert(moveHandle != _setCommand.end());

            if (moveHandle != _setCommand.end()) {
                moveHandle->second->handle(elem);
            }
        }
        // std::cout << elem.command << " " <<  elem.axis.first << " " << elem.axis.second << " " << __FILE__ << " " << __func__  << " " << __LINE__ << std::endl;
        if (elem.command != "dimension") {
            _prevData = elem;
        }
        getPrevData();
        index++;
    }

    setResultForRender();
}

void Algo::setResultForRender() {
    // auto lineHandle = _setCommand["line_to"];
    
    // assert(lineHandle != _setCommand.end());

    // std::transform(lineHandle->_result.begin(), lineHandle->_result.end(), std::back_inserter(_result));
}

Data Algo::getPrevData() {
    return this->_prevData;
}

void Algo::testInit() {
    for (const auto& data : _parser->_info) {
        for (const auto& elem : this->_setCommand) {
            elem.second->handle(data);
        }
    }
}