#ifndef CONSOLE_H
#define CONSOLE_H

#include "../algo/algo.h"
#include "renderer.h"

class Console : public Renderer {
    private:
        std::shared_ptr<Algo> _algo;

        DimensionAlgo _dimension;

        std::vector<AxisAlgo> _axisRender;

    public:
        explicit Console(std::shared_ptr<Algo> algo) : _algo{algo} {

        }

        void handleRequest() override; 

        void render() override;

        void getDataForRendering();
};

#endif