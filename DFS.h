#ifndef PROJECT_MILSTONE2_DFS_H
#define PROJECT_MILSTONE2_DFS_H

#include <stack>
#include <unordered_set>
#include "Searchable.h"
#include "StackSearcher.h"

template<typename solution, class T>
class DFS : public StackSearcher<solution, T> {
public:
    solution search(Searchable<T> *searchable) {
        this->openList.clear();
        this->evaluateNodes = 0;
        vector<State<T>*> close;
        this->addOpenList(searchable->getInitialState());
        while (this->openListSize() > 0) {
            State<T>* state = this->popOpenList();
            if (!this->containsClose(close, state))
                close.push_back(state);

            if (searchable->isGoalState(state))
                return this->backTrace(state, searchable);

            vector<State<T>*> states = searchable->getAllPossibleStates(state);
            for (State<T>* s : states) {
                if (!this->containsClose(close, s) && ! this->openContains(s)) {
                    this->addOpenList(s);
                }
            }
        }
    }
};

#endif //PROJECT_MILSTONE2_DFS_H
