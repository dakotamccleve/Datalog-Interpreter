#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->data = description;
    this->newLines = line;
}

std::string Token::toString() {
    return "(" + tokenToString(type) + ",\"" + data + "\"," + std::to_string(newLines) + ")";
}

std::string Token::tokenToString(TokenType type) {
    switch(type) {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case FACTS:
            return "FACTS";
        case SCHEMES:
            return "SCHEMES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case ENUM_EOF:
            return "EOF";
        default:
            return "Uh Oh";
    }
}

std::string Token::getTokenType() {
    return this->tokenToString(type);
}

std::string Token::getData() {
    return this->data;
}