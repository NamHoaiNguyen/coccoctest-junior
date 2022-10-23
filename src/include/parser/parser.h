#ifndef PARSER_H
#define PARSER_H

// #include "command.h"
// #include "dimension_command.h"
// #include "line_command.h"
// #include "move_command.h"
#include "../common/command_data.h"
#include "../execution/state.h"

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// struct Data {
//     std::string command;
//     std::pair<std::string, std::string> axis;
// };

class Parser : public State {
    private:    
        std::string _filePath;

        std::string delimiter = ", ";

        std::string delim = " ";

        std::vector<Data> _info;

        std::unordered_set<std::string> _setCommands;
        
        // std::unordered_map<std::string, std::shared_ptr<Command>> m_setCo,mand;

        int a = 1; 

        int b = 2;

        friend class Algo;

    public: 
        // int a = 1; 

        // int b = 2;

        Parser() = default;

        explicit Parser(std::string&& pathFile) : _filePath{pathFile} {

        }

        void handleRequest();

        void validateFile();

        void readFile();

        void parseData(std::ifstream& fp);

        void createCommand();

        // std::shared_ptr<Command> createDimensionCommand();

        // std::shared_ptr<Command> createMoveCommand();

        // std::shared_ptr<Command> createLineCommand();
};  

#endif