#ifndef RENDERER_H
#define RENDERER_H

#include "../execution/state.h"

class Renderer : virtual public State {
    public:
        virtual void render() = 0;
};

#endif