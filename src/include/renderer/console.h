#ifndef CONSOLE_H
#define CONSOLE_H

#include "renderer.h"

class Console : public Renderer {
    public:
        void render() override;
};

#endif