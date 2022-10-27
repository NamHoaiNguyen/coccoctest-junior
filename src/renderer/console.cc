#include "console.h"

#define GRID_SIZE   4
#define MAX_GRID_SIZE   52

void Console::handleRequest() {
    this->getDataForRendering();
    this->render();
}

void Console::getDataForRendering(){
    this->_dimension = _algo->getDimension();
    this->_axisRender = _algo->getAxisAlgo();
}

void Console::render() {
    std::cout << "Size of dimension " << this->_dimension.dimension  << std::endl;
    std::cout << "List of square units which robot move through!!!" << std::endl;
    for (const auto& elem : _axisRender) {
        std::cout << elem.x << " " << elem.y << std::endl;
    }

    int gridSize = this->_dimension.dimension;
    int cellSize = GRID_SIZE;
    int total = gridSize * cellSize;
    char c;
    int index = 0;

    // std::cout << "List of square units which robot move through after converting to axis of console!!!" << std::endl;

    for (auto& elem : _axisRender) {
        elem.x = (GRID_SIZE / 2) + GRID_SIZE * elem.x;
        elem.y = (GRID_SIZE / 2) + GRID_SIZE * elem.y;
        // std::cout << elem.x << " " << elem.y << std::endl;
    }


    std::cout << "RENDER TO CONSOLE!!!" << std::endl;

    if (gridSize > MAX_GRID_SIZE) {
        std::cout << "Care!!! Size of grid is too large! The image rendered to console can be wrong!!!" << std::endl;
    }

    for (int i = 0; i <= total; i++) {
        for (int k = 0; k <= total; k++) {
            if (i % cellSize == 0) {
                c = '-';
            } else if (k % cellSize == 0) {
                c = '|';
            } else if (i == _axisRender[index].x && k == _axisRender[index].y) {
                c = '+';
                ++index;
            }
                else { 
                c = ' ';
            }
            std::cout << c;
        }
        std::cout << std::endl;
    }
}