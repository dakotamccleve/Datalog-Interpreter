//
// Created by dakot on 5/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string tableName, std::vector<std::string> newHeaders) {
    headers = std::move(newHeaders);
    name = std::move(tableName);
}

void Relation::setName(std::string newName) {
    name = newName;
}

void Relation::addTuple(const Tuple &tuple) {
    tupleSet.insert(tuple);
}

std::vector<std::string> Relation::getHeaders() {
    return headers;
}

std::string Relation::toString() {
    std::string str;
    str += name + "( ";
    for (const std::string& h : headers) {
        str += h + ", ";
    }
    str +=")\n";
    for(Tuple t : tupleSet) {
        str += t.toString() + "\n";
    }
    return str;
}

std::string Relation::getName() {
    return name;
}

std::set<Tuple> Relation::getTuples() {
    return tupleSet;
}

Relation Relation::select(int index, std::string value) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    for (Tuple t : tupleSet) {
        if(t.getValues()[index] == value) {
            r.addTuple(t);
        }
    }
    return r;
}

Relation Relation::select(int index, int index2) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    for (Tuple t: tupleSet) {
        if(t.getValues()[index] == t.getValues()[index2]) {
            r.addTuple(t);
        }
    }
    return r;
}

Relation Relation::project(std::vector<int> indices) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    for(Tuple t : tupleSet) {
        Tuple retTuple;
        for(unsigned int i = 0; i < indices.size(); i++) {
            retTuple.addValue(t.getValues().at(indices.at(i)));
        }
        r.addTuple(retTuple);
    }
    return r;
}

Relation Relation::rename(std::vector<std::string> IDs) {
    Relation r;
    r.name = name;
    r.tupleSet = tupleSet;
    if(IDs.size() > 0) {
        r.headers = IDs;
    }
    return r;
}

int Relation::numOfTuples(std::vector<std::string> vars) {
    int num = 0;
    for(Tuple t: tupleSet) {
        std::stringstream ss;
        for(unsigned int j = 0; j < t.getValues().size(); j++) {
            num++;
        }
    }
    if(num != 0) {
        return (num / vars.size());
    }
    else return 1;
}

void Relation::presentTuples(std::vector<int> positions, std::vector<std::string> IDs, int number) {
    std::set<int> indicesToSkip = {};
    for (unsigned int i = 0; i < IDs.size(); i++) {
        if (IDs.at(i)[0] == '\'') {
            indicesToSkip.insert(i);
        }
    }
    unsigned int idsToPrint = positions.size() - indicesToSkip.size();
    unsigned int totalItemsToPrint = idsToPrint;
    if(totalItemsToPrint) {
        for (Tuple t: tupleSet) {
            unsigned int totalPrintedItems = 0;
            std::string str = "  ";
            unsigned int indexCounter = 0;
            unsigned int loopCount = 1;
            for(unsigned int i = 0; i < t.getValues().size(); i++) {
                if (indexCounter == IDs.size()) {
                    indexCounter = 0;
                    loopCount++;
                }
                if (indicesToSkip.count(indexCounter)) {

                }
                else if (((totalPrintedItems + 1) / loopCount == IDs.size() - indicesToSkip.size()) || idsToPrint == 1) {
                    totalPrintedItems++;
                    str+= IDs[i % positions.size()] + "=" + t.getValues()[i];
                    if(totalItemsToPrint == totalPrintedItems) {
                        str += "\n";
                    }
                    else if (i < t.getValues().size()) {
                        str += "\n";
                    }
                }
                else {
                    totalPrintedItems++;
                    str += IDs[i % positions.size()] + "=";
                    str += t.getValues()[i] + ", ";
                }
                indexCounter++;
            }
            std::cout << str;
        }
    }
}

Relation Relation::join(Relation rel1) {
    Relation newRelation;
    std::vector<int> toAddInts;
    newRelation.headers = headers;
    for (unsigned int i = 0; i < rel1.headers.size(); i++) {
        bool isCopy = false;
        for (unsigned int j = 0; j < headers.size(); j++) {
            if (!isCopy) {
                if (headers.at(j) != rel1.headers.at(i)) {
                    isCopy = false;
                }
                else {
                    isCopy = true;
                }
            }
        }
        if (!isCopy) {
            newRelation.headers.push_back(rel1.headers.at(i));
            toAddInts.push_back(i);
        }
    }
    for (Tuple t : tupleSet) {
        for (Tuple tup : rel1.tupleSet) {
            if (isJoinable(t, tup, headers, rel1.headers)) {
                Tuple newTuple = t;
                for (unsigned int k = 0; k < toAddInts.size(); k++) {
                    newTuple.addValue(tup.getValues().at(toAddInts.at(k)));
                }
                newRelation.addTuple(newTuple);
            }
        }
    }
    return newRelation;
}


bool Relation::isJoinable(Tuple tup1, Tuple t2, std::vector<std::string> header1, std::vector<std::string> header2) {
    bool completelyUnique = true;
    if(header1 == header2 && tup1.getValues() != t2.getValues()) {
        return false;
    }
    else if(header1.size() > 1 && header2.size() > 1 && header1.at(1) == header2.at(0) && header2.at(1) == header1.at(0)) {
        if(tup1.getValues().at(0) == t2.getValues().at(1) && tup1.getValues().at(1) == t2.getValues().at(0)) {
            return true;
        }
        else {
            return false;
        }
    }
    for(unsigned int i = 0; i < header1.size(); i++) {
        for(unsigned int j = 0; j < header2.size(); j++) {
            if (header1.at(i) == header2.at(j)) {
                completelyUnique = false;
                if (tup1.getValues().at(i) == t2.getValues().at(j)) {
                    return true;
                }
            }
        }
    }
    if (completelyUnique) {
        return true;
    }
    else {
        return false;
    }
}

bool Relation::unite(const Relation& ruleEvalRel) {
    bool returnVal = false;
    for(auto t : ruleEvalRel.tupleSet) {
        if(tupleSet.insert(t).second) {

            returnVal = true;
            if (headers.size() != 0) {
                std::cout << "  ";
            }
            for (unsigned int j = 0; j < headers.size(); j++) {
                std::cout << headers.at(j) + "=" + t.getValues().at(j);
                if (j < headers.size()-1) {
                    std::cout << ", ";
                }
            }
            if (!headers.empty()) {
                std::cout << "\n";
            }
        }
    }
    return returnVal;
}