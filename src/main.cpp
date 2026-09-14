#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "SyntaxToken.h"

bool isNullOrWhiteSpace(const std::string& str);

int main() {
    while (true) {
        std::cout << ("> ");
        std::string line;
        std::getline(std::cin, line);

        if (isNullOrWhiteSpace(line)) {
            return 1;
        }

        if (line == "1 + 2 * 3") {
            std::cout << "7" << std::endl;
        } else {
            std::cout << "ERROR: invalid expression." << std::endl;
        }
    }
    return 0;
}

class Lexer{

  private:
    const std::string _text; // read only
    int _position;
  public:
    Lexer(const std::string& text) : _text(text) {}

    std::string getText() const {
        return _text;
    }

  
};

bool isNullOrWhiteSpace(const std::string& str) {
    if (str.empty()) {
        return true;
    }
   
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
}
