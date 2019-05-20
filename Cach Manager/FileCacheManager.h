#ifndef PROJECT_MILSTONE2_FILECACHEMANAGER_H
#define PROJECT_MILSTONE2_FILECACHEMANAGER_H


#include <unordered_map>
#include "CacheManager.h"
#include "convertor.h"
#include "Searchable.h"
#include <fstream>

#define SEPERATOR '$'

template<class problem, class solution>
class FileCacheManager : public CacheManager<problem, solution> {

    string path;
    unordered_map<string, string> problemsMap;
    convertor<problem, solution> *objectConvertor;

public:
    FileCacheManager(string path, convertor<problem, solution> *objectConvert) {
        this->path = path;
        this->objectConvertor = objectConvert;
        LoadSolutionString();
    }

    void LoadSolutionString() {
        ifstream in(this->path);
        string lineBuffer;
        stringstream strStream;
        string solutionStr, problemStr;

        while (getline(in, lineBuffer)) {

            strStream.str(lineBuffer);
            getline(strStream, problemStr, SEPERATOR);
            getline(strStream, solutionStr, SEPERATOR);

            this->problemsMap[problemStr] = solutionStr;
            problemStr.clear();
            solutionStr.clear();
            strStream.clear();
        }
        in.close();
    }

    void SaveSolutions() {
        ofstream out(this->path);
        for(auto data : this->problemsMap){
            out << data.first << SEPERATOR << data.second << endl;
        }
        out.close();
    }

    bool isSolutionExists(const problem &p) {
        string pString = this->objectConvertor->problemToString(p);
        if (problemsMap.find(pString) != problemsMap.end())
            return true;

        return false;
    }

    void addSolution(problem p, solution s) {
        string stringProblem = this->objectConvertor->problemToString(p);
        string stringSolution = this->objectConvertor->solutionToString(s);

        this->problemsMap[stringProblem] = stringSolution;
    }

    solution getSolution(problem p) {
        string pString = this->objectConvertor->problemToString(p);
        string solutionStr = this->problemsMap[pString];
        return this->objectConvertor->stringToSolution(solutionStr);
    }

    ~FileCacheManager(){
        SaveSolutions();
    }

};

#endif //PROJECT_MILSTONE2_FILECACHEMANAGER_H
