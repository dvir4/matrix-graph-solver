#ifndef PROJECT_MILSTONE2_MATRIXCONVERTOR_H
#define PROJECT_MILSTONE2_MATRIXCONVERTOR_H


#include "Searchable.h"
#include "convertor.h"
#include "matrixProblem.h"

class matrixConvertor : public convertor<Searchable<pair<int,int>>*, string> {
    vector<Searchable<pair<int,int>>*> allocatedSearcher;
public:
    Searchable<pair<int,int>>* stringToProblem(vector<string> str);
    string problemToString(Searchable<pair<int,int>>* searchable);
    string solutionToString(string s);
    string stringToSolution(string str);
    ~matrixConvertor();
};


#endif //PROJECT_MILSTONE2_MATRIXCONVERTOR_H
