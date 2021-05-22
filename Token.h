#pragma once

#include <string>

enum TokenType {
    COLON, COLON_DASH, ENUM_EOF, COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, RULES, QUERIES, FACTS, SCHEMES, ID, STRING, COMMENT, ADD, MULTIPLY, UNDEFINED
};

class Token
{
private:
    TokenType type;
    std::string data;
    int newLines;

public:
    Token(TokenType type, std::string description, int line);
    std::string tokenToString(TokenType type);
    std::string toString();
    std::string getTokenType();
    std::string getData();
};

