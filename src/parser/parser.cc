#include "parser.h"

using namespace std;

void Parser::handleRequest() {
    validateFile();
} 

void Parser::validateFile() {
    fs::path p (_filePath);

    if (!fs::exists(p)) {
        std::cout << "Please recheck! The file doesn't exist!!!" << std::endl;
        exit(1);
    }

    try {
        if (fs::is_regular_file(p)) {
            readFile();
        } else {
            std::cout << "Not a file!!!" << std::endl;
            exit(1);
        }
    }
    catch(fs::filesystem_error const& ex) {
        std::cout << "Not a file!\n" << ex.what() << '\n';
        exit(1);
    }
}

void Parser::readFile() {
    std::ifstream fp;
    fp.open(_filePath, std::ios::in);
    if(!fp.good()) {
        std::cout<<"File Not Found\n";
        exit(1);
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
        
        // std::cout << "check new line " << new_line << std::endl;
        std::stringstream s(new_line);
        while (s >> word >> axis) {
            std::string token;

            /*tolower*/
            std::transform(word.begin(), word.end(), word.begin(), [](const auto& elem){
                return std::tolower(elem);
            });

            word.erase(std::remove_if(word.begin(), word.end(), [](const auto& c){
                return !std::isalnum(c);
            }), word.end());

            DataCommand data;
            data.command = word;
            _setCommands.insert(word);

            std::size_t prev = 0, pos;
            while ((pos = axis.find_first_of(" ,", prev)) != std::string::npos)  // only look for . and ~s
            {
                
                if (pos > prev) {
                    token = axis.substr(prev, pos-prev);
                    try {
                        data.axis.first = std::stoi(token);
                        parseFirst = true;
                    } catch (std::exception& e) {
                        std::cout << "Syntax error of file is wrong!!!"  << "\n"
                                  << "Please correct syntax of command" << std::endl;
                        exit(1);
                    }
                }
                prev = pos+1;
            }
            if (prev < line.length()) {
                token = axis.substr(prev, std::string::npos);
                if (data.command == "dimension") {
                    try {
                        data.axis.first = std::stoi(token);
                        parseFirst = true;
                    } catch (std::exception& e) {
                        std::cout << "Syntax error of file is wrong!!!"  << "\n"
                                  << "Please correct syntax of command" << std::endl;
                        exit(1);
                    }
                    data.axis.second = 0;
                } else {
                    try {
                        data.axis.second = std::stoi(token);
                        parseFirst = true;
                    } catch (std::exception& e) {
                        std::cout << "Syntax error of file is wrong!!!"  << "\n"
                                  << "Please correct syntax of command" << std::endl;
                        exit(1);
                    }
                }
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

    int dimen = (*dimension).axis.first;

    auto data = std::find_if(_info.begin(), _info.end(), [&dimen](const auto &elem){
        return (((elem.axis.first) >= dimen || (elem.axis.second) >= dimen) && elem.command != "dimension");
    });

    if (data != _info.end()) {
        std::cout << "Syntax of file is wrong!!!"  << "\n"
                  << "Axis of command shouldn't be larger than size of dimension!!!" << std::endl; 
        exit(1);
    }
}