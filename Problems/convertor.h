#ifndef PROJECT_MILSTONE2_CONVERTOR_H
#define PROJECT_MILSTONE2_CONVERTOR_H

using namespace std;

#include <string>
#include <vector>
#include <sstream>


template <class problem, class solution>
class convertor {

public:
    virtual problem stringToProblem(vector<string> str) = 0;
    virtual string problemToString(problem p) = 0;
    virtual string solutionToString(solution s) = 0;
    virtual solution stringToSolution(string str) = 0;
    virtual ~convertor(){};
};

#endif //PROJECT_MILSTONE2_CONVERTOR_H
