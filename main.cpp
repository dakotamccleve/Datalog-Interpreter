#include "Lexer.h"
#include "Parser.h"

#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    std::ifstream inputFile;
    inputFile.open(argv[1]);
    std::ostringstream fout;
    fout << inputFile.rdbuf();
    std::string inputString = fout.str();

    lexer->Run(inputString);
    parser->Parse(lexer->getTokens());
 //   lexer->printTokens();


    delete parser;
    delete lexer;

    return 0;
}