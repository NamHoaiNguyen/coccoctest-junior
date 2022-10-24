#include "console.h"

void Console::handleRequest() {
    this->render();
}

void Console::render() {
    std::cout << "Test render for console" << std::endl;
}
