#include "program_context.h"

void ProgramContext::setState(std::shared_ptr<State> state) {
    this->_state = state;
}

void ProgramContext::applyState() {
    this->_state->handleRequest();
}

void ProgramContext::setStateM(std::unique_ptr<State> state) {
    this->m_state = std::move(state);
}

void ProgramContext::applyStateM() {
    this->m_state->handleRequest();
}