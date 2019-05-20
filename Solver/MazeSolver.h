#ifndef PROJECT_MILSTONE2_MAZESOLVER_H
#define PROJECT_MILSTONE2_MAZESOLVER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Solver.h"
#include "State.h"
#include "Searchable.h"
#include "ISearcher.h"
#include "matrixProblem.h"

using namespace std;

class MazeSolver : public Solver<Searchable<pair<int,int>>*, string> {
private:
    ISearcher<vector<State<pair<int, int>> *>, pair<int, int>> *searcher;
public:
    MazeSolver(ISearcher<vector<State<pair<int, int>> *>, pair<int, int>> *searcher){
        this->searcher = searcher;
    }

    string Solve(Searchable<pair<int,int>> *matrix);
};


#endif //PROJECT_MILSTONE2_MAZESOLVER_H
