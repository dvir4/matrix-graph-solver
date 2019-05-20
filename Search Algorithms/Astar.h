#ifndef PROJECT_MILSTONE2_ASTAR_H
#define PROJECT_MILSTONE2_ASTAR_H

#include <set>
#include "PriorityQueueSearcher.h"


template<typename solution, class T>
class Astar : public PriorityQueueSearcher<solution, T> {
public:
    /**
     * the function giving a soulition to a problem according to the A*
     * algrithem
     * @param searchable
     * @return
     */
    solution search(Searchable<T> *searchable) {
        this->openList.clear();
        this->evaluateNodes = 0;
        State<T> *start = searchable->getInitialState();
        setHeuristic(start,searchable);
        this->addOpenList(start);
        vector<State<T>*> close;
        while (this->openListSize() > 0) {
            State<T> *n = this->popOpenList();
            close.push_back(n);
            if (searchable->isGoalState(n))
                return this->backTrace(n, searchable);
            vector<State<T>*> states = searchable->getAllPossibleStates(n);
            for (State<T> *s : states) {
                if (!containsClose(close, s) && !this->openContains(s)) {
                    setHeuristic(s,searchable);
                    this->addOpenList(s);
                } else {
                    if (!containsClose(close, s)) {
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

    bool containsClose(vector<State<T>*> &close, State<T> *s) {
        for (auto it = close.begin(); it != close.end(); it++) {
            if (s->equals(*it))
                return true;
        }
        return false;
    }
  

    void setHeuristic(State<T> *s, Searchable<T> *searchable) {
        T currState = s->getState();
        T goalState = searchable->getGoalState();
        int distance = abs(goalState.first - currState.first) + abs(goalState.second - currState.second);
        int currCost = s->getCost();
        State<T>* cameFromState = s->getFather();
        if(cameFromState != nullptr){
            T FatherState = cameFromState->getState();
            int fatherDistance = abs(goalState.first - FatherState.first) + abs(goalState.second - FatherState.second);
            s->setCost(distance + currCost - fatherDistance);
        } else{
            s->setCost(distance + currCost);
        }

    }

};

#endif //PROJECT_MILSTONE2_ASTAR_H
