#include "algo.h"

namespace Traits {
    template<typename T>
    struct TypeCommand {
        using Type = void;
    };

    template<>
    struct TypeCommand<Dimension> {
        using Type = Dimension;
    };

    template<>
    struct TypeCommand<Move> {
        using Type = Move;
    };

    template<>
    struct TypeCommand<Line> {
        using Type = Line;
    };
}

void Algo::handleRequest() {
    // std::cout << "algo handle request" << std::endl;
    // std::cout << _parser->a << " " << _parser->b << std::endl;
    initialize();
    execute();
}

void Algo::initialize() {
    for (const auto& elem : _parser->_setCommands) {
        // std::cout << elem << std::endl;
        if (elem == "dimension") {
            // std::cout << "check create dimension" << std::endl;
            _setCommand[elem] = std::make_shared<Dimension>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        } else if (elem == "line_to") {
            // std::cout << "check create line_to" << std::endl;
            _setCommand[elem] = std::make_shared<Line>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        } else if (elem == "move_to") {
            // std::cout << "check create move_to" << std::endl;
            _setCommand[elem] = std::make_shared<Move>();
            _setCommand[elem]->addAlgo(this->weak_from_this());
        }
    }

    // testInit();
}

void Algo::execute() {
    // for (const auto& elem : _setCommand) {
    //     std::cout << elem.first << std::endl;
    // }

    for (auto elem : _parser->_info) {
        // std::cout << elem.command << " " <<  elem.axis.first << " " << elem.axis.second << " " << __FILE__ << " " << __func__  << " " << __LINE__ << std::endl;
        if (elem.command == "dimension") {
            std::cout << "check execute dimension 1" << std::endl;
            auto dimensionHandle = _setCommand.find(elem.command);

            assert(dimensionHandle != _setCommand.end());

            if (dimensionHandle != _setCommand.end()) {
                // dimensionHandle->second->addAlgo(this->weak_from_this());
                dimensionHandle->second->handle(elem);
            }
        } else if (elem.command == "line_to") {
            std::cout << "check execute line_to 2" << std::endl;

            auto lineHandle = _setCommand.find(elem.command);

            assert(lineHandle != _setCommand.end());

            if (lineHandle != _setCommand.end()) {
                // lineHandle->second->addAlgo(this->weak_from_this());
                lineHandle->second->handle(elem);
            }
        } else if (elem.command == "move_to") {
            std::cout << "check execute move_to 1" << std::endl;

            auto moveHandle = _setCommand.find(elem.command);

            assert(moveHandle != _setCommand.end());

            if (moveHandle != _setCommand.end()) {
                // moveHandle->second->addAlgo(this->weak_from_this());
                moveHandle->second->handle(elem);
            }
        }
        // std::cout << elem.command << " " <<  elem.axis.first << " " << elem.axis.second << " " << __FILE__ << " " << __func__  << " " << __LINE__ << std::endl;
        if (elem.command != "dimension") {
            _prevData = elem;
        }
        getPrevData();
    }
}

Data Algo::getPrevData() {
    // std::cout << this->_prevData.command << " " << this->_prevData.axis.first << " " << this->_prevData.axis.second << " " << __FILE__ << " " << __func__ << " " << __LINE__ << std::endl;

    return this->_prevData;
}

void Algo::testInit() {
    for (const auto& data : _parser->_info) {
        for (const auto& elem : this->_setCommand) {
            elem.second->handle(data);
        }
    }
}