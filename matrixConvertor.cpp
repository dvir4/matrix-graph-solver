#include "matrixConvertor.h"

Searchable<pair<int,int>>* matrixConvertor::stringToProblem(vector<string> str) {
  Searchable<pair<int,int>> *searchable = new matrixProblem(str);
  allocatedSearcher.push_back(searchable);
  return searchable;
}

string matrixConvertor::problemToString(Searchable<pair<int, int>> *searchable) {
   return searchable->to_string();
}

string matrixConvertor::solutionToString(string s) {
      return s;
}

string matrixConvertor::stringToSolution(string str) {
    return str;
}

matrixConvertor::~matrixConvertor() {
    for(auto searcher : allocatedSearcher){
        if(searcher != nullptr)
            delete searcher;
    }
}
