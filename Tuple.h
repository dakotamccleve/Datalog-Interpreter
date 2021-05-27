//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_TUPLE_H
#define CS236_PROJECT_3_TUPLE_H

#include <string>
#include <vector>


class Tuple {
public:
    Tuple() {}
    Tuple(std::string name, std::vector<std::string> values);
    void addValue(std::string value);
    std::vector<std::string> getValues();
    bool operator< (const Tuple t) const;

private:
    std::vector<std::string> tupleValues;
    std::string relationName;
};


#endif //CS236_PROJECT_3_TUPLE_H
