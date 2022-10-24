#ifndef BITMAP_H
#define BITMAP_H

#include "../algo/algo.h"
#include "renderer.h"

class Bitmap : public Renderer {
    private:
        std::shared_ptr<Algo> _algo;

    public:
        explicit Bitmap(std::shared_ptr<Algo> algo) : _algo{algo} {

        }

        void handleRequest() override; 

        void render() override;
        
};

#endif