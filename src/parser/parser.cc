#include "parser.h"

using namespace std;

void Parser::handleRequest() {
    validateFile();
} 

void Parser::validateFile() {
    try {
        if (fs::is_regular_file(_filePath)) {
            readFile();
        }
    }
    catch(fs::filesystem_error const& ex) {
        std::cout << "Invalid path!\n" << ex.what() << '\n';
    }
}

void Parser::readFile() {
    std::ifstream fp;
    fp.open(_filePath, std::ios::in);
    if(!fp.good()) {
        std::cout<<"File Not Found\n";
        return;
    }
    parseData(fp);

    fp.close();
}

void Parser::parseData(std::ifstream& fp) {
    std::string line, word, axis, axis_x, axis_y;
    while (getline(fp, line)) {
        bool parseFirst = false;
      
        /*Remove space, tabs*/
        std::regex space_re(R"(\s+)");
 
        std::string new_line = std::regex_replace(line, space_re, " ");
  
        /*Handle space before and after comma*/
        auto index_comma = std::find_if(new_line.begin(), new_line.end(), [](const auto& elem){return elem == ',';});
        auto index_space_before = std::find_if(index_comma - 1, index_comma, [](const auto& elem){return elem == ' ';});


        if (index_comma != new_line.end() && index_space_before != new_line.end()) {
            new_line.erase(std::remove(index_space_before, new_line.end(), ' '), new_line.end());
        }
        
        std::cout << "check new line " << new_line << std::endl;
        std::stringstream s(new_line);
        while (s >> word >> axis) {
            std::string token;
            size_t beg, pos = 0;

            /*tolower*/
            std::transform(word.begin(), word.end(), word.begin(), [](const auto& elem){
                return std::tolower(elem);
            });


            DataCommand data;
            data.command = word;
            _setCommands.insert(word);

            while ((beg = axis.find_first_not_of(delimiter, pos)) != std::string::npos) {
                pos = axis.find_first_of(delimiter, beg + 1);
                
                token = axis.substr(beg, pos - beg);
                if (!parseFirst) {
                    data.axis.first = token;
                    parseFirst = true;
                }    
            }
            if (data.command != "dimension") {
                data.axis.second = token;
            }        
           
            this->_info.push_back(data);
        }
    }

    validateData();
}

void Parser::validateData() {
    auto dimension = std::find_if(_info.begin(), _info.end(), [](const auto &elem){
        return elem.command == "dimension";
    });

    if (dimension == _info.end()) {
        std::cout << "Syntax error of file is wrong!!!"  << "\n"
                  << "Please provide dimension of square grid." << std::endl;
        exit(1);
    }

    int dimen;
    try {
        dimen = std::stoi((*dimension).axis.first);
    } catch (std::exception& e) {
        std::cout << "Please provide true syntax of dimension" << std::endl;
        exit(1);
    }

    auto data = std::find_if(_info.begin(), _info.end(), [&dimen](const auto &elem){
        return ((std::stoi(elem.axis.first) >= dimen || std::stoi(elem.axis.second) >= dimen) && elem.command != "dimension");
    });

    if (data != _info.end()) {
        std::cout << "Syntax of file is wrong!!!"  << "\n"
                  << "Axis of command shouldn't be larger than size of dimension!!!" << std::endl; 
        exit(1);
    }
}