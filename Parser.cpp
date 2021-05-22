//
// Created by dakot on 5/15/2021.
//

#include "Parser.h"

Parser::Parser() {}

Parser::~Parser() {}


void Parser::Parse(std::vector<Token *> tokens) {
    try {
        datalogProgram(tokens);
    }
    catch(Token* err) {
        std::cout << "Failure!\n  " << err->toString() << std::endl;
        return;
    }
    std::cout <<"Success!" << std::endl;
    std::cout << datalog.toString();
}

void Parser::datalogProgram(std::vector<Token *> tokens) {
    if(tokens.at(it)->getTokenType() == "SCHEMES") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "COLON") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    scheme(tokens);
    schemeList(tokens);

    if(tokens.at(it)->getTokenType() == "FACTS") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "COLON") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    factList(tokens);

    if(tokens.at(it)->getTokenType() == "RULES") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "COLON") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    ruleList(tokens);

    if(tokens.at(it)->getTokenType() == "QUERIES") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "COLON") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    query(tokens);
    queryList(tokens);

    if(tokens.at(it)->getTokenType() == "EOF") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
}

void Parser::scheme(std::vector<Token*> tokens) {
    int schemeIt = it;
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "LEFT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    idList(tokens);
    if(tokens.at(it)->getTokenType() == "RIGHT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }

    Predicate* scheme = new Predicate(tokens.at(schemeIt)->getData());
    datalog.addScheme(scheme);
    schemeIt++;
    while(schemeIt < it) {
        if(tokens.at(schemeIt)->getTokenType() == "ID") {
            datalog.getSchemes().at(datalog.getSchemes().size()-1)->addParameter(new Parameter(tokens.at(schemeIt)));
        }
        schemeIt++;
    }
}

void Parser::schemeList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
        scheme(tokens);
        schemeList(tokens);
    }
    else {
        return;
    }
}

void Parser::idList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "COMMA") {
        this->peekToken(tokens, "COMMA");
        this->peekToken(tokens, "ID");
        idList(tokens);
    }
    else {
        return;
    }
}

void Parser::stringList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "COMMA") {
        this->peekToken(tokens, "COMMA");
        this->peekToken(tokens, "STRING");
        stringList(tokens);
    }
    else {
        return;
    }
}

void Parser::fact(std::vector<Token*> tokens) {
    int factIt = it;
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "LEFT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "STRING") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    stringList(tokens);
    if(tokens.at(it)->getTokenType() == "RIGHT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "PERIOD") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
        Predicate* fact = new Predicate(tokens.at(factIt)->getData());
    datalog.addFact(fact);
    factIt++;
    while(factIt < it) {
        if(tokens.at(factIt)->getTokenType() == "STRING") {
            datalog.getFacts().at(datalog.getFacts().size()-1)->addParameter(new Parameter(tokens.at(factIt)));
            datalog.addToDomain(tokens.at(factIt)->getData());
        }
        factIt++;
    }

}
void Parser::factList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
        fact(tokens);
        factList(tokens);
    }
    else {
        return;
    }
}

void Parser::rule(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
    }
    else {
        throw tokens.at(it);
    }
    Rule* rule = new Rule(headPredicate(tokens));
    this->peekToken(tokens, "COLON_DASH");
    rule->addPredicate(predicate(tokens));
    std::vector<Predicate*> predList = predicateList(tokens);
    for(unsigned int i = 0; i < predList.size(); i++) {
        rule->addPredicate(predList.at(i));
    }
    datalog.addRule(rule);
    peekToken(tokens, "PERIOD");
}

void Parser::ruleList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
        rule(tokens);
        ruleList(tokens);
    }
    else {
        return;
    }
}

void Parser::query(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
        datalog.addQuery(predicate(tokens));
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "Q_MARK") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
}

void Parser::queryList(std::vector<Token*> tokens) {
    if(tokens.at(it)->getTokenType() == "ID") {
        query(tokens);
        queryList(tokens);
    }
    else {
        return;
    }
}


Predicate* Parser::headPredicate(std::vector<Token*> tokens) {
    int headPredicateIt = it;
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "LEFT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    idList(tokens);
    if(tokens.at(it)->getTokenType() == "RIGHT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    Predicate* headPredicate = new Predicate(tokens.at(headPredicateIt)->getData());
    headPredicateIt++;
    while(headPredicateIt < it) {
        if(tokens.at(headPredicateIt)->getTokenType() == "ID") {
            headPredicate->addParameter(new Parameter(tokens.at(headPredicateIt)));
        }
        headPredicateIt++;
    }
    return headPredicate;
}

Predicate * Parser::predicate(std::vector<Token*> tokens) {
    int predicateIt = it;
    if(tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "LEFT_PAREN") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    if(tokens.at(it)->getTokenType() == "STRING" || tokens.at(it)->getTokenType() == "ID") {
    }
    else {
        throw tokens.at(it);
    }
    Parameter* param = parameter(tokens);
    std::vector<Parameter*> paramList = parameterList(tokens);
    this->peekToken(tokens, "RIGHT_PAREN");
    Predicate* predicate = new Predicate(tokens.at(predicateIt)->getData());
    predicateIt++;
    predicate->addParameter(param);
    for(unsigned int i = 0; i < paramList.size(); i++) {
        predicate->addParameter(paramList[i]);
    }
    return predicate;
}

std::vector<Predicate *> Parser::predicateList(std::vector<Token*> tokens) {
    std::vector<Predicate*> predicateListV;
    if(tokens.at(it)->getTokenType() == "COMMA") {
        it++;
    }
    else {
        return{};
    }
    predicateListV.push_back(predicate(tokens));
    std::vector <Predicate*> recursivePredicate = predicateList(tokens);
    for(unsigned int i = 0; i < recursivePredicate.size(); i++) {
        predicateListV.push_back(recursivePredicate.at(i));
    }
    return predicateListV;
}

Parameter* Parser::parameter(std::vector<Token*> tokens) {
    int parameterIt = it;
    if(tokens.at(it)->getTokenType() == "STRING" || tokens.at(it)->getTokenType() == "ID") {
        it++;
    }
    else {
        throw tokens.at(it);
    }
    return new Parameter(tokens.at(parameterIt)); //TODO:: Something with expressions maybe?
}

std::vector<Parameter*> Parser::parameterList(std::vector<Token*> tokens) {
    std::vector<Parameter*> paramList = {};
    if(tokens.at(it)->getTokenType() == "COMMA") {
        it++;
    }
    else {
        return {};
    }
    paramList.push_back(parameter(tokens));
    std::vector<Parameter*>recursiveParamList = parameterList(tokens);
    for(unsigned int i = 0; i < recursiveParamList.size(); i++) {
        paramList.push_back(recursiveParamList.at(i));
    }
    return paramList;
}

void Parser::peekToken(std::vector<Token*> tokens, std::string checkStr) {
    if(tokens.at(it)->getTokenType() == checkStr){
        it++;
    }
    else {
        throw tokens.at(it);
    }
}