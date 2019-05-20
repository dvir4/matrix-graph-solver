#ifndef PROJECT_MILSTONE2_COMPARECOST_H
#define PROJECT_MILSTONE2_COMPARECOST_H

#include "State.h"

using namespace std;

template<class T>
struct CompareCost {
public:
    bool operator()(State<T> *s1,State<T>  *s2) const {
        return s1->getCost() < s2->getCost();
    }
};

#endif //PROJECT_MILSTONE2_COMPARECOST_H
