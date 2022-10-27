#ifndef PROGRAM_CONTEXT_H
#define PROGRAM_CONTEXT_H

#include "state.h"

#include <memory>

class ProgramContext {
    private:
        std::shared_ptr<State> _state;
        std::unique_ptr<State> m_state;
        
    public:
        void setState(std::shared_ptr<State> state); 

        void applyState();

        void setStateM(std::unique_ptr<State> state);

        void applyStateM();
};

#endif