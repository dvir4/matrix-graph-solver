#ifndef PROJECT_MILSTONE2_ISEARCHER_H
#define PROJECT_MILSTONE2_ISEARCHER_H

#include "Searchable.h"

template<typename solution, class T>
class ISearcher{
public:
    virtual solution search(Searchable<T> *searchable) = 0;
    virtual int getNumberOfNodesEvaluate() = 0;
    virtual ~ISearcher(){}
};


#endif //PROJECT_MILSTONE2_ISEARCHER_H
