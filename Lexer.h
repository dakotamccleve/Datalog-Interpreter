#pragma once

#include <vector>
#include <string>
#include <cctype>
#include "Automaton.h"
#include "Token.h"


class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    std::vector<Token*> getTokens();
    
    void printTokens();

};

