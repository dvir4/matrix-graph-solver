#ifndef PROJECT_MILSTONE2_SEARCHABLE_H
#define PROJECT_MILSTONE2_SEARCHABLE_H

#include "State.h"
#include <vector>

using namespace std;

template<class T>
class Searchable{
public:
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoalState(State<T>* s) = 0;
    virtual vector<State<T>*> getAllPossibleStates(State<T> *s) = 0;
    virtual T getGoalState() = 0;
    virtual string to_string() = 0;
    virtual ~Searchable(){}
};



#endif //PROJECT_MILSTONE2_SEARCHABLE_H
