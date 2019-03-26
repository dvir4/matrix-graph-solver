#ifndef PROJECT_MILSTONE2_BFS_H
#define PROJECT_MILSTONE2_BFS_H


#include <stack>
#include <unordered_set>
#include "Searchable.h"
#include "queueSearcher.h"

template<typename solution, class T>
class BFS : public queueSearcher<solution, T> {
public:
    
    solution search(Searchable<T> *searchable) {
        this->openList.clear();
        this->evaluateNodes = 0;
        vector<State<T>*> close;
        this->addOpenList(searchable->getInitialState());
        while (this->openListSize() > 0) {
            State<T> *state = this->popOpenList();
            if (!this->containsClose(close, state))
                close.push_back(state);

            if (searchable->isGoalState(state))
                return this->backTrace(state, searchable);

            vector<State<T>*> states = searchable->getAllPossibleStates(state);
            for (State<T> *s : states) {
                if (!this->containsClose(close, s) && !this->openContains(s)) {
                    this->addOpenList(s);
                }
            }
        }
    }
};


#endif //PROJECT_MILSTONE2_BFS_H
