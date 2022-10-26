#include "algo.h"
#include "bitmap.h"
#include "console.h"
#include "parser.h"
#include "renderer.h"
#include "program_context.h"

#include <iostream>

int main(int argc, char* argv[])
{
    std::string path{};         // path to directory
    
     if (argc < 2) {
        std::cerr << "Syntax error!  \n" 
                  << "Provide exe file and path to text file!!!" << std::endl; 
        return 1;
    } else {
        path = std::move(argv[1]);
    }

    std::cout << path << " " << std::endl;

    ProgramContext context;

    auto parser = std::make_shared<Parser>(std::move(path));
    auto algo = std::make_shared<Algo>(parser);
    std::shared_ptr<Renderer> console = std::make_shared<Console>(algo);


    context.setState(parser);
    context.applyState();

    context.setState(algo);
    context.applyState();

    context.setState(console);
    context.applyState();
    
}