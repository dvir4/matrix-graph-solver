#ifndef PROJECT_MILSTONE2_STATE_H
#define PROJECT_MILSTONE2_STATE_H

#include<string>
using namespace std;

template<class T>
class State {
    T state;
    double cost;
    State<T> *cameFrom;

public:

    State(T state,double cost, State<T> * cameFrom){
        this->state = state;
        this->cost = cost;
        this->cameFrom = cameFrom;
    }

    void setCost(double cost) {
        this->cost = cost;
    }

    void setCameFrom(State<T> *cameFrom) {
        this->cameFrom = cameFrom;
    }

    T getState() const {
        return state;
    }

    double getCost(){
        return this->cost;
    }

    State<T>* getFather(){
        return this->cameFrom;
    }

    bool equals(State<T> *state){
        return this->state == state->state;
    }

    ~State(){};
};


#endif //PROJECT_MILSTONE2_STATE_H
