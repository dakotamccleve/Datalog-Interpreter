#include "Lexer.h"
#include "MatcherAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"

#include <vector>
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(SCHEMES, "Schemes"));
    automata.push_back(new MatcherAutomaton(COMMA, ","));
    automata.push_back(new MatcherAutomaton(PERIOD, "."));
    automata.push_back(new MatcherAutomaton(Q_MARK, "?"));
    automata.push_back(new MatcherAutomaton(LEFT_PAREN, "("));
    automata.push_back(new MatcherAutomaton(RIGHT_PAREN, ")"));
    automata.push_back(new MatcherAutomaton(MULTIPLY, "*"));
    automata.push_back(new MatcherAutomaton(ADD, "+"));
    automata.push_back(new MatcherAutomaton(RULES, "Rules"));
    automata.push_back(new MatcherAutomaton(QUERIES, "Queries"));
    automata.push_back(new MatcherAutomaton(FACTS, "Facts"));
    automata.push_back(new IDAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::Run(std::string& input) {

    int lineNumber = 1;

    while(!input.empty()) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];
        while(isspace(input.at(0))) {
            if (input.at(0) == '\n') {
                lineNumber++;
            }

            input.erase(0, 1);
            if (input.empty()) {
                   Token* newToken = new Token(ENUM_EOF,"", lineNumber);
                tokens.push_back(newToken);
                return;
            }
        }
            for(unsigned int i = 0; i < automata.size(); i++) {
                int inputRead = automata.at(i)->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                  maxAutomaton = automata[i];
                }
            }

            if(maxRead > 0) {
                Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
                lineNumber += maxAutomaton->NewLinesRead();
                if(newToken->getTokenType() != "COMMENT") {
                    tokens.push_back(newToken);
                }
            }

            else {
                maxRead = 1;
                Token *newToken = maxAutomaton->CreateToken(UNDEFINED,input.substr(0,maxRead), lineNumber);
                tokens.push_back(newToken);
            }

            input.erase(0, maxRead);
        }

        if(input.empty()) {
               Token* newToken = new Token(ENUM_EOF, "", lineNumber);
            tokens.push_back(newToken);
            return;
        }
}

std::vector<Token*> Lexer::getTokens() {
    return this->tokens;
}

void Lexer::printTokens() {
    for(int i = 0; i < (int)tokens.size(); i++) {
        std::cout << tokens.at(i)->toString() << std::endl;
    }
    std::cout << "Total Tokens = " << (int)tokens.size();
}
