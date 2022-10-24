#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"
#include "../common/command_data.h"

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

class Move : public Command {
    private:
        struct Axis {
            int axis_x;
            int axis_y;
        };

        std::shared_ptr<Command> _command;

        std::weak_ptr<Algo> _algo;

        std::vector<Data> _historyMoves;

        std::vector<Axis> _history;

    public:
        void handle(const Data& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        void setUpParams(const Data& data);
};

#endif