#ifndef SERVER_SIDE_SOLVER_H
#define SERVER_SIDE_SOLVER_H

using namespace std;

template<class problem, class solution>
class Solver {
public:
    virtual solution Solve(problem p) = 0;
};


#endif //SERVER_SIDE_SOLVER_H
