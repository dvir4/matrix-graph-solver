#include "MazeSolver.h"
#include<iostream>

string convertToPath(vector<State<pair<int, int>> *> sol) {
    vector<string> path;
    cout << sol.begin().operator[](0)->getCost() << endl;
    for (State<pair<int, int>> *state : sol) {
        if (state->getFather() != nullptr) {
            pair<int, int> location = state->getState();
            pair<int, int> cameFromLocation = state->getFather()->getState();
            if (location.second == cameFromLocation.second) {
                if (location.first > cameFromLocation.first) {
                    path.push_back("Down");
                } else {
                    path.push_back("Up");
                }
            } else {
                if (location.second > cameFromLocation.second) {
                    path.push_back("Right");
                } else {
                    path.push_back("Left");
                }
            }
        }
    }
    string result;
    for (auto it = --path.end(); it != --path.begin(); it--) {
        result += *it;
        result += ",";
    }
    result.pop_back();
    return result;
}

string MazeSolver::Solve(Searchable<pair<int, int>> *matrix){
    vector<State<pair<int, int>> *> sol = this->searcher->search(matrix);
    string result = convertToPath(sol);
    cout <<"number of nodes evaluate"<< searcher->getNumberOfNodesEvaluate() <<
    endl;
    return result;
}

vector<string> splitLine(string line, string separator) {
    vector<string> ans;
    string part = "";
    string ch = "";
    for (int i = 0; i < line.size(); i++) {
        ch = line[i];
        if (ch == separator) {
            ans.push_back(part);
            part = "";
            continue;
        }
        part += line[i];
    }
    ans.push_back(part);
    return ans;
}
