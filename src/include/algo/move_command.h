#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"
#include "../common/axis.h"
#include "../common/command_data.h"

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

class Move : public Command {
    private:
        // struct Axis {
        //     int axis_x;
        //     int axis_y;
        // };

        std::shared_ptr<Command> _command;

        std::weak_ptr<Algo> _algo;

        std::vector<DataCommand> _historyMoves;

        std::vector<AxisAlgo> _history;

    public:
        void handle(const DataCommand& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        std::vector<AxisAlgo> getAxis() override; 

        DimensionAlgo getDimension() override; 

        void setUpParams(const DataCommand& data);
};

#endif