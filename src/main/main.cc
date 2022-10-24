#include "algo.h"
#include "bitmap.h"
#include "console.h"
#include "parser.h"
#include "renderer.h"
#include "program_context.h"

#include <iostream>

int validateInput(int argc, char* argv[]) {
    std::string path{};         // path to directory
    
    if (argc < 1) {
        std::cerr << "Syntax error!  \n" 
                  << "> coccoc “many wsords” [path to directory]" << std::endl; 
        return 1;
    } else if (argc < 2) {
        path = std::move("./");
    } else {
        std::cout << "come here" << std::endl;        
        path = std::move(argv[1]);
    }

    std::cout << path << " " << std::endl;

    return 0;
}

int main(int argc, char* argv[])
{
    // validateInput(argc, argv);

    std::string path{};         // path to directory
    
    if (argc < 1) {
        std::cerr << "Syntax error!  \n" 
                  << "> coccoc “many wsords” [path to directory]" << std::endl; 
        return 1;
    } else if (argc < 2) {
        path = std::move("./");
    } else {
        // std::cout << "come here" << std::endl;        
        path = std::move(argv[1]);
    }

    // std::cout << path << " " << std::endl;

    // Parser p;
    // p.handleRequest();
    // p.parseData();
    // p.readFile();

    ProgramContext context;

    auto parser = std::make_shared<Parser>(std::move(path));
    auto algo = std::make_shared<Algo>(parser);
    std::shared_ptr<Renderer> bitmap = std::make_shared<Bitmap>(algo);
    std::shared_ptr<Renderer> console = std::make_shared<Console>(algo);


    context.setState(parser);
    context.applyState();

    context.setState(algo);
    context.applyState();

    context.setState(bitmap);
    context.applyState();

    context.setState(console);
    context.applyState();
    
}