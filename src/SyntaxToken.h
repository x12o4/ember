#pragma once

#include <string>
#include <any>

enum class SyntaxKind {
    NumberToken, 
    WhiteSpaceToken, 
    PlusToken, 
    MinusToken,
    StarToken, 
    SlashToken,
    OpenParenthesisToken, 
    CloseParanthesisToken,
    BadToken, 
    EndOfFileToken,
};

class SyntaxToken{
    public:
    SyntaxToken(SyntaxKind kind, int position, std::string text, std::any value) : kind(kind), position(position), text(std::move(text)), value(std::move(value)) {}

    SyntaxKind getKind() const {return kind;}
    int getPosition() const {return position;}
    const std::string& getText() const {return text;}
    const std::any& getValue() const { return value; }

    private:
    SyntaxKind kind;
    int position;
    std::string text;
    std::any value;
};