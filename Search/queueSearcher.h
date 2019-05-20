#ifndef PROJECT_MILSTONE2_QUEUESEARCHER_H
#define PROJECT_MILSTONE2_QUEUESEARCHER_H

#include <deque>
#include "ISearcher.h"

template<typename solution, class T>
class queueSearcher : public ISearcher<solution,T> {
    // common member
    // initialize priority queue ordered by cost value.
protected:
    int evaluateNodes;
    deque<State<T>*> openList;
public:
    queueSearcher() {
        this->evaluateNodes = 0;
    }

    // common function
    int getNumberOfNodesEvaluate() {
        return this->evaluateNodes;
    }

    int openListSize() {
        return (int) this->openList.size();
    }

    bool openContains(State<T> *s) {
        for (auto it = openList.begin(); it != openList.end(); it++) {
            if (s->equals(*it))
                return true;
        }
        return false;
    }

    // need to be implement on search algorithems.
    virtual solution search(Searchable<T> *searchable) = 0;

    State<T>* popOpenList() {
        this->evaluateNodes++;
        State<T> *s = openList.front();
        openList.pop_front();
        return s;
    }

    void addOpenList(State<T> *s) {
        this->openList.push_back(s);
    }

    bool containsClose(vector<State<T>*> &close, State<T> *s) {
        for (auto it = close.begin(); it != close.end(); it++) {
            if (s->equals(*it))
                return true;
        }
        return false;
    }
    // common function
    solution backTrace(State<T> *s, Searchable<T> *searchable) {

        vector<State<T> *> finalPath;

        State<T> *startState = searchable->getInitialState();
        State<T> *currState = s;
        while (!(currState->equals(startState))) {
            finalPath.push_back(currState);
            currState = currState->getFather();
        }
        finalPath.push_back(currState);
        return finalPath;
    }

};


#endif //PROJECT_MILSTONE2_QUEUESEARCHER_H
