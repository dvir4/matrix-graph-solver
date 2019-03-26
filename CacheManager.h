#ifndef PROJECT_MILSTONE2_CACHEMANAGER_H
#define PROJECT_MILSTONE2_CACHEMANAGER_H

using namespace std;

#include <map>

template<class problem, class solution>
class CacheManager {
public:
    /**
     * the function loading a solution as a string
     */
    virtual void LoadSolutionString() = 0;
    virtual void SaveSolutions() = 0;
    /**
     * the function check if problem was solved
     * @param p problem object
     * @return true if the solution was exist else false
     */
    virtual bool isSolutionExists(const problem &p) = 0;
    /*
    the function adds a problem with its solution
    */
    virtual void addSolution(problem p, solution s) = 0;
    virtual solution getSolution(problem p) = 0;

    virtual ~CacheManager() {}

};


#endif //PROJECT_MILSTONE2_CACHEMANAGER_H
