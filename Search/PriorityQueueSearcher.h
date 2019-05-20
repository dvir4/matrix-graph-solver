#ifndef PROJECT_MILSTONE2_PRIORITYQUEUESEARCHER_H
#define PROJECT_MILSTONE2_PRIORITYQUEUESEARCHER_H

#include <queue>
#include <algorithm>
#include <set>
#include "ISearcher.h"
#include "CompareCost.h"

template<typename solution, class T>
class PriorityQueueSearcher : public ISearcher<solution,T> {
    // initialize priority queue ordered by cost value.
protected:
    int evaluateNodes;
    multiset<State<T>* ,CompareCost<T>> openList;


public:
    PriorityQueueSearcher(){
        this->evaluateNodes = 0;
    }

    int getNumberOfNodesEvaluate() {
        return this->evaluateNodes;
    }

    int openListSize(){
        return (int) this->openList.size();
    }

    bool openContains(State<T> *s){
        for(auto it = this->openList.begin(); it != this->openList.end(); it++){
            if(s->equals(*it))
                return true;
        }
        return false;
    }

    // need to be implement on search algorithems.
    virtual solution search(Searchable<T> *searchable) = 0;

    State<T>* popOpenList(){
        this->evaluateNodes++;
        auto it = this->openList.begin();
        State<T> *s = *it;
        this->openList.erase(it);
        return s;
    }

    void addOpenList(State<T> *s){
        this->openList.insert(s);
    }

    solution backTrace(State<T> *s, Searchable<T> *searchable){

        vector<State<T>*> finalPath;

        State<T> *startState = searchable->getInitialState();
        State<T> *currState = s;
        while(!(currState->equals(startState))){
            finalPath.push_back(currState);
            currState = currState->getFather();
        }
        finalPath.push_back(currState);
        return finalPath;
    }

};


#endif //PROJECT_MILSTONE2_PRIORITYQUEUESEARCHER_H
