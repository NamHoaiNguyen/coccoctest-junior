#ifndef LINE_COMMAND_H
#define LINE_COMMAND_H

#include "command.h"
#include "../common/command_data.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

class Line : public Command {
    private:
        struct LineAxis {
            int x;
            int y;
        };

        std::shared_ptr<Command> _command;

        std::weak_ptr<Algo> _algo;

        std::unordered_map<std::string, std::shared_ptr<Command>> _commands;

        /*Save axis of */
        std::vector<LineAxis> _historyLine;

        /*Save axis of all points needed to render*/
        std::vector<LineAxis> _result;

    public:
        void handle(const Data& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        void setUpParams(const Data& data);

        void execute();

        void midPoint(int X1, int Y1, int X2, int Y2);
};

#endif