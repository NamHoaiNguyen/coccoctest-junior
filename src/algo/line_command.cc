#include "line_command.h"
#include "algo.h"
#include <cmath>
#include "math.h"

using namespace std;

void Line::handle(const DataCommand& data) {
    setUpParams(data);
    execute();
}

void Line::setUpParams(const DataCommand& data) {
    AxisAlgo axis;

    axis.x = (data.axis.first);
    axis.y = (data.axis.second);
    this->_historyLine.push_back(axis);
}

void Line::addAlgo(std::weak_ptr<Algo> algo) {
    this->_algo = algo;
}

std::vector<AxisAlgo> Line::getAxis() {
    return this->_result;
}

DimensionAlgo Line::getDimension() {
    
} 


void Line::execute() {
    /*
    Get the current position
    This position can come from axis from MOVE_TO or LINE_TO command.
    */
    DataCommand prevData;

    if (auto subscriber = this->_algo.lock(); subscriber) {
        prevData = subscriber->getPrevData();
    }

    int prevAxis_x = (prevData.axis.first);
    int prevAxis_y = (prevData.axis.second);

    GenerateLine(prevAxis_x, prevAxis_y, _historyLine.back().x, _historyLine.back().y);
}


int Line::roundFloat(float n)
{
    if (n - (int)n < 0.5)
        return (int)n;
    return (int)(n + 1);
}
 
// Function for line generation
void Line::GenerateLine(int x0, int y0, int x1, int y1)
{
 
    // Calculate dx and dy
    int dx = x1 - x0;
    int dy = y1 - y0;
 
    int step;
 
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
 
    // Calculate x-increment and y-increment for each step
    float x_incr = (float)dx / step;
    float y_incr = (float)dy / step;
 
    // Take the initial points as x and y
    float x = x0;
    float y = y0;
 
    for (int i = 0; i < step + 1; i++) {
        AxisAlgo axis;
        axis.x = roundFloat(x);
        axis.y = roundFloat(y);
        _result.push_back(axis);
        x += x_incr;
        y += y_incr;
    }
}