#ifndef LINE_COMMAND_H
#define LINE_COMMAND_H

#include "command.h"
#include "../common/axis.h"
#include "../common/command_data.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

struct LineAxis {
    int x;
    int y;
};

class Line : public Command {
    private:
        std::shared_ptr<Command> _command;

        std::weak_ptr<Algo> _algo;

        std::unordered_map<std::string, std::shared_ptr<Command>> _commands;

        /*Save axis of */
        std::vector<AxisAlgo> _historyLine;

        /*Save axis of all points needed to render*/
        // std::vector<Axis> _result;

        std::vector<AxisAlgo> _result;

        int start_x = 0;

        int start_y = 0;

    public:
        void handle(const DataCommand& data) override;

        void addAlgo(std::weak_ptr<Algo> algo) override;

        std::vector<AxisAlgo> getAxis() override; 

        DimensionAlgo getDimension() override; 

        void setUpParams(const DataCommand& data);

        void execute();

        void midPoint(int X1, int Y1, int X2, int Y2);

        int roundt(float n);

        void DDALine(int X1, int Y1, int X2, int Y2);

        void checkResult();
};

#endif