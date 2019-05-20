#ifndef PROJECT_MILSTONE2_BestFirstSearch_H
#define PROJECT_MILSTONE2_BestFirstSearch_H

#include <set>
#include "PriorityQueueSearcher.h"
#include "CompareCost.h"

template<typename solution, class T>
class BestFirstSearch : public PriorityQueueSearcher<solution, T> {
public:
    solution search(Searchable<T> *searchable) {
        this->openList.clear();
        this->evaluateNodes = 0;
        this->addOpenList(searchable->getInitialState());
        vector<State<T>*> close;
        while (this->openListSize() > 0) {
            State<T> *n = this->popOpenList();
            close.push_back(n);
            if (searchable->isGoalState(n))
                return this->backTrace(n,searchable);
            vector<State<T>*> states = searchable->getAllPossibleStates(n);
            for (State<T> *s : states) {
                if (!containsClose(close,s) && !this->openContains(s)) {
                    this->addOpenList(s);
                } else {
                    if (!containsClose(close,s)) {
                        this->reserveMinimum(s);
                    }
                }
            }
        }
    }

    void reserveMinimum(State<T> *s) {
        for (auto it = this->openList.begin(); it != this->openList.end(); it++) {
            State<T> *currState = *it;
            if (s->equals(currState)) {
                if (s->getCost() >= currState->getCost())
                    break;
                this->openList.erase(it);
                this->openList.insert(s);
            }
        }
    }

    bool containsClose(vector<State<T>*> &close,State<T> *s) {
        for (auto it = close.begin(); it != close.end(); it++) {
            if (s->equals(*it))
                return true;
        }
        return false;
    }
};


#endif //PROJECT_MILSTONE2_BestFirstSearch_H
