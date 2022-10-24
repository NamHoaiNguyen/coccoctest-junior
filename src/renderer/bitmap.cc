#include "bitmap.h"

void Bitmap::handleRequest() {
    this->render();
}

void Bitmap::render() {
    std::cout << "Test render for bitmap!" << std::endl;
}
