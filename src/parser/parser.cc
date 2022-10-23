#include "parser.h"

void Parser::handleRequest() {
    std::cout << "parser handle request" << std::endl;
    std::cout << _filePath << std::endl;

    createCommand();
    validateFile();
} 

void Parser::createCommand() {
    // this->_dimension = std::make_shared<Dimension>();
    // this->_move = std::make_shared<Move>();
    // this->_line = std::make_shared<Line>();
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
    std::cout << "parser read file" << std::endl;

    std::ifstream fp;
    fp.open(_filePath, std::ios::in);
    if(!fp.good()) {
        std::cout<<"File Not Found\n";
        return;
    }

    // std::string line, word, axis;
    // while (getline(fp, line)) {
    //     std::stringstream s(line);
    //     while (s >> word >> axis) {
    //         std::string token;
    //         size_t beg, pos = 0;

    //         Data data;
    //         data.command = word;

    //         while ((beg = axis.find_first_not_of(delimiter, pos)) != std::string::npos) {
    //             pos = axis.find_first_of(delimiter, beg + 1);
                
    //             token = axis.substr(beg, pos - beg);
    //             data.axis.first = token;
    //         }
    //         data.axis.second = token;
    //         std::cout << data.command << " " << data.axis.first << " " << data.axis.second << std::endl;
    //     }
    // }

    // while (getline(fp, line)) {
    //     std::stringstream s(line);
    //     while (s >> word) {
    //         const std::string s = "Hello, everyone! This is: COSC-1436, SP18";

    //         std::regex words_regex("[^\\s.,:;!?]+");
    //         auto words_begin = std::sregex_iterator(word.begin(), word.end(), words_regex);
    //         auto words_end = std::sregex_iterator();
            
    //         Data data;
    //         for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    //             std::cout << (*i).str() << '\n';
    //             data.com
    //         }
    //     }
    // }

    parseData(fp);

    fp.close();
}

void Parser::parseData(std::ifstream& fp) {
    std::cout << "parser parse data" << std::endl;

    std::string line, word, axis;
    while (getline(fp, line)) {
        bool parseFirst = false;
        std::stringstream s(line);
        while (s >> word >> axis) {
            std::string token;
            size_t beg, pos = 0;

            std::transform(word.begin(), word.end(), word.begin(), [](const auto& elem){
                return std::tolower(elem);
            });

            // std::cout << word << " " << axis << std::endl;

            Data data;
            data.command = word;
            _setCommands.insert(word);

            while ((beg = axis.find_first_not_of(delimiter, pos)) != std::string::npos) {
                pos = axis.find_first_of(delimiter, beg + 1);
                
                token = axis.substr(beg, pos - beg);
                if (!parseFirst) {
                    data.axis.first = token;
                    parseFirst = true;
                }    
                // std::cout << data.axis.first << std::endl;
            }
            if (data.command != "dimension") {
                data.axis.second = token;
            }        
            this->_info.push_back(data);
        }
    }

    // for (const auto& elem : _info) {
    //     std::cout << elem.command << " " << elem.axis.first << " "<< elem.axis.second << " " << __FILE__ << " " << __func__ <<  std::endl;
    // }
}