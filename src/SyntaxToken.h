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
    CloseParenthesisToken,
    BadToken, 
    EndOfFileToken,
};

std::ostream& operator<<(std::ostream& os, const SyntaxKind& kind) {

    switch (kind) {

        case SyntaxKind::EndOfFileToken: return os << "EndOfFileToken";

        case SyntaxKind::NumberToken: return os << "NumberToken";

        case SyntaxKind::WhiteSpaceToken: return os << "WhiteSpaceToken";

        case SyntaxKind::PlusToken: return os << "PlusToken";

        case SyntaxKind::MinusToken: return os << "MinusToken";

        case SyntaxKind::StarToken: return os << "StarToken";

        case SyntaxKind::SlashToken: return os << "SlashToken";

        case SyntaxKind::OpenParenthesisToken: return os << "OpenParenthesisToken";

        case SyntaxKind::CloseParenthesisToken: return os << "CloseParanthesisToken";

        case SyntaxKind::BadToken: return os << "BadToken";

        default: return os << "UnknownToken";

    }

}

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