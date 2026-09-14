#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "SyntaxToken.h"
#include <optional>
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
    char Current() {
        if (_position >= _text.length()) {
            return '\0'; // return null if out of bounds
        }
        return _text[_position]; // return current character
    }
    void Next(){
        _position++;
    }

  public:
    Lexer(const std::string& text) : _text(text) {}

    std::string getText() const {
        return _text;
    }
    
    SyntaxToken NextToken(){
        // numbers, operators, whitespace.
        if(std::isdigit(Current())){
            auto start = _position;
            while(isdigit(Current())){
                Next();
            }

            auto length = _position - start;
            auto text = _text.substr(start, length);
            
            return SyntaxToken(SyntaxKind::NumberToken, start, text, std::stoi(text));


        }
        if(std::isspace(Current())){
            auto start = _position;
            while(std::isspace(Current())){
                Next();
            }

            auto length = _position - start;
            auto text = _text.substr(start, length);
            
            return SyntaxToken(SyntaxKind::WhiteSpaceToken, start, text, std::stoi(text));

        }

        if(Current() == '+'){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::PlusToken, start, "+", std::nullopt);
        }

        else if(Current() == '-'){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::MinusToken, start, "+", std::nullopt);
        }

        else if(Current() == '*'){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::StarToken, start, "+", std::nullopt);
        }

        else if(Current() == '/'){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::SlashToken, start, "+", std::nullopt);
        }

        else if(Current() == '('){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::OpenParenthesisToken, start, "+", std::nullopt);
        }

        else if(Current() == ')'){
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::CloseParanthesisToken, start, "+", std::nullopt);
        }

        else if(Current() == '\0'){
            return SyntaxToken(SyntaxKind::EndOfFileToken, _position, "", std::nullopt);
        }

        else{
            auto start = _position;
            Next();
            return SyntaxToken(SyntaxKind::BadToken, start, std::string(1, Current()), std::nullopt);
        }

        
        
    }
  
};

bool isNullOrWhiteSpace(const std::string& str) {
    if (str.empty()) {
        return true;
    }
   
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
}

