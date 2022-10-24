#ifndef CONSOLE_H
#define CONSOLE_H

#include "../algo/algo.h"
#include "renderer.h"

class Console : public Renderer {
    private:
        std::shared_ptr<Algo> _algo;

    public:
        explicit Console(std::shared_ptr<Algo> algo) : _algo{algo} {

        }

        void handleRequest() override; 

        void render() override;
        
};

#endif