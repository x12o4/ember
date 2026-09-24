#pragma once

#include <string>
#include <any>
#include <ostream>
#include <utility>

enum class SyntaxKind {
    NumberExpression,
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

inline std::ostream& operator<<(std::ostream& os, const SyntaxKind& kind) {

    switch (kind) {

        case SyntaxKind::EndOfFileToken: return os << "EndOfFileToken";

        case SyntaxKind::NumberExpression: return os << "NumberExpression";

        case SyntaxKind::NumberToken: return os << "NumberToken";

        case SyntaxKind::WhiteSpaceToken: return os << "WhiteSpaceToken";

        case SyntaxKind::PlusToken: return os << "PlusToken";

        case SyntaxKind::MinusToken: return os << "MinusToken";

        case SyntaxKind::StarToken: return os << "StarToken";

        case SyntaxKind::SlashToken: return os << "SlashToken";

        case SyntaxKind::OpenParenthesisToken: return os << "OpenParenthesisToken";

        case SyntaxKind::CloseParenthesisToken: return os << "CloseParenthesisToken";

        case SyntaxKind::BadToken: return os << "BadToken";

        default: return os << "UnknownToken";

    }

}
class SyntaxNode
{
public:
    virtual ~SyntaxNode() = default;
    virtual SyntaxKind getKind() const = 0;
};

class SyntaxToken : public SyntaxNode {
    public:
    SyntaxToken(SyntaxKind kind, int position, std::string text, std::any value) : kind(kind), position(position), text(std::move(text)), value(std::move(value)) {}

    SyntaxKind getKind() const override {return kind;}
    int getPosition() const {return position;}
    const std::string& getText() const {return text;}
    const std::any& getValue() const { return value; }

    private:
    SyntaxKind kind;
    int position;
    std::string text;
    std::any value;
};


class ExpressionSyntax : public SyntaxNode
{

};

class NumberSyntax final : public ExpressionSyntax
{
public:
    NumberSyntax(SyntaxToken numberToken) : numberToken(std::move(numberToken))
    {

    }
    SyntaxKind getKind() const override
    {
        return SyntaxKind::NumberExpression;
    }
};