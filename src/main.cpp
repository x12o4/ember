#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <optional>
#include <vector>
#include "SyntaxToken.h"

bool isNullOrWhiteSpace(const std::string& str);

class Lexer {

  private:
    const std::string _text; // read only
    int _position;

    char Current() {
        if (_position >= _text.length()) {
            return '\0'; // return null if out of bounds
        }
        return _text[_position]; // return current character
    }

    void Next() {
        _position++;
    }

  public:
    Lexer(const std::string& text) : _text(text), _position(0) {}

    std::string getText() const {
        return _text;
    }

    SyntaxToken NextToken() {
        // numbers, operators, whitespace.

        if (_position >= _text.length()) {
            return SyntaxToken(SyntaxKind::EndOfFileToken, _position, std::string(), std::nullopt);
        }

        if (std::isdigit(static_cast<unsigned char>(Current()))) {
            auto start = _position;
            while (std::isdigit(static_cast<unsigned char>(Current()))) {
                Next();
            }

            auto length = _position - start;
            auto text = _text.substr(start, length);

            return SyntaxToken(SyntaxKind::NumberToken, start, text, std::stoi(text));
        }

        if (std::isspace(static_cast<unsigned char>(Current()))) {
            auto start = _position;
            while (std::isspace(static_cast<unsigned char>(Current()))) {
                Next();
            }

            auto length = _position - start;
            auto text = _text.substr(start, length);

            return SyntaxToken(SyntaxKind::WhiteSpaceToken, start, text, std::any{});
        }

        auto start = _position;

        if (Current() == '+') {
            Next();
            return SyntaxToken(SyntaxKind::PlusToken, start, "+", std::any{});
        }
        else if (Current() == '-') {
            Next();
            return SyntaxToken(SyntaxKind::MinusToken, start, "-", std::any{});
        }
        else if (Current() == '*') {
            Next();
            return SyntaxToken(SyntaxKind::StarToken, start, "*", std::any{});
        }
        else if (Current() == '/') {
            Next();
            return SyntaxToken(SyntaxKind::SlashToken, start, "/", std::any{});
        }
        else if (Current() == '(') {
            Next();
            return SyntaxToken(SyntaxKind::OpenParenthesisToken, start, "(", std::any{});
        }
        else if (Current() == ')') {
            Next();
            return SyntaxToken(SyntaxKind::CloseParenthesisToken, start, ")", std::any{});
        }
        else {
            Next();
            return SyntaxToken(SyntaxKind::BadToken, start, _text.substr(start, 1), std::any{});
        }
    }
};
class Parser{
    private:
        int _position;
        std::vector<SyntaxToken> tokens; // readonly
        SyntaxToken Peek(int offset){
            auto index = _position + offset;
            if(index >= tokens.size()){
                return tokens.back();
            }
            return tokens[index];
        }
        SyntaxToken Current = Peek(0);
    public: 
    Parser(std::string text){
        
        auto lexer = Lexer(text);
        SyntaxToken token(SyntaxKind::BadToken, 0, "", std::any{});
        do{
            token = lexer.NextToken();

            if(token.getKind() != SyntaxKind::WhiteSpaceToken && token.getKind() != SyntaxKind::BadToken){
                tokens.push_back(token);
            }
        } while(token.getKind() != SyntaxKind::EndOfFileToken);
        
    }
};
int main() {
    while (true) {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        if (isNullOrWhiteSpace(line)) {
            return 1;
        }

        auto lexer = Lexer(line);

        while (true) {
            auto token = lexer.NextToken();
            if (token.getKind() == SyntaxKind::EndOfFileToken) {
                break;
            }
            std::cout << token.getKind() << ": " << token.getText();
            if (token.getValue().has_value()) {
                std::cout << " " << std::any_cast<int>(token.getValue());
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

bool isNullOrWhiteSpace(const std::string& str) {
    if (str.empty()) {
        return true;
    }

    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
}