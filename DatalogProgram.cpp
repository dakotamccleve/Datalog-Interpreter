//
// Created by dakot on 5/15/2021.
//

#include "DatalogProgram.h"

std::string DatalogProgram::toString() {
    std::stringstream ss;
    ss << "Schemes(" << schemes.size() << "):\n";
    for (unsigned int i = 0; i < schemes.size(); i++) {
        ss << "  " << schemes.at(i)->toString() << "\n";
    }
    ss << "Facts(" << facts.size() << "):\n";
    for (unsigned int i = 0; i < facts.size(); i++) {
        ss << "  " << facts.at(i)->toString() << ".\n";
    }
    ss << "Rules(" << rules.size() << "):\n";
    for (unsigned int i = 0; i < rules.size(); i++) {
        ss << "  " << rules.at(i)->toString();
    }
    ss << "Queries(" << queries.size() << "):\n";
    for (unsigned int i = 0; i < queries.size(); i++) {
        ss << "  " << queries.at(i)->toString() << "?\n";
    }
    ss << "Domain(" << domain.size() << "):\n";
    for (std::set<std::string>::iterator i = domain.begin(); i != domain.end(); i++) {
        ss << "  " << *i << '\n';
    }
    return ss.str();
}
