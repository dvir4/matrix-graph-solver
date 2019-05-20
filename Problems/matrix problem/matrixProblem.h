#ifndef PROJECT_MILSTONE2_MATRIXPROBLEM_H
#define PROJECT_MILSTONE2_MATRIXPROBLEM_H


using namespace std;

#include <string>
#include "Searchable.h"

class matrixProblem : public Searchable<pair<int, int>> {
    vector<string> matrixStr;
    vector<vector<int>> matrix;
    int lenght;
    int width;
    pair<int, int> startState;
    pair<int, int> goalState;
    vector<State<pair<int,int>>*> allocatedStates;

public:
    matrixProblem(vector<string> matrixStr) {
        initializeMatrix(matrixStr);
        this->matrixStr = matrixStr;
    }

    void initializeMatrix(vector<string> &matrixStr) {
        string exitStr = matrixStr.back();
        matrixStr.pop_back();
        string startStr = matrixStr.back();
        matrixStr.pop_back();

        vector<string> coordinates = splitLine(exitStr,",");
        int xExit = stoi(coordinates[0]);
        int yExit = stoi(coordinates[1]);

        coordinates = splitLine(startStr,",");
        int xStart = stoi(coordinates[0]);
        int yStart = stoi(coordinates[1]);


        pair<int, int> enter = {xStart, yStart};
        pair<int, int> exit = {xExit,yExit};

        this->startState = enter;
        this->goalState = exit;


        vector<int> matrixLine;
        vector<vector<int>> matrixFinal;
        // for each string line in the matrix.
        for (string matrixLineStr : matrixStr) {
            vector<string> parameters = splitLine(matrixLineStr, ",");
            // for each parameter, convert string value to int.
            for (string param : parameters) {
                matrixLine.push_back(stoi(param));
            }
            matrixFinal.push_back(matrixLine);
            matrixLine.clear();
        }

        this->matrix = matrixFinal;
        this->width = matrixFinal[0].size();
        this->lenght = matrixFinal.size();
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

    State<pair<int, int>>* getInitialState() {
        State<pair<int, int>>* initialState = new State<pair<int, int>>(this->startState, 0, nullptr);
        allocatedStates.push_back(initialState);
        return initialState;
    }

    bool isGoalState(State<pair<int, int>> *s) {
        return s->getState() == this->goalState;
    }

    vector<State<pair<int, int>>*> getAllPossibleStates(State<pair<int, int>> *s) {
        vector<State<pair<int, int>>*> states;
        pair<int, int> stateLocation = s->getState();
        int i = stateLocation.first;
        int j = stateLocation.second;
        int maxCol = this->width - 1;
        int maxRow = this->lenght - 1;

        if (i - 1 >= 0) {
            if (matrix[i - 1][j] != -1) {
                State<pair<int, int>>* up = new State<pair<int, int>>(make_pair(i - 1, j), s->getCost() + matrix[i - 1][j],s);
                states.push_back(up);
                allocatedStates.push_back(up);
            }
        }

        if (i + 1 <= maxRow) {
            if (matrix[i + 1][j] != -1) {
                State<pair<int, int>>* down = new State<pair<int, int>>(make_pair(i + 1, j), s->getCost() + matrix[i + 1][j],s);
                states.push_back(down);
                allocatedStates.push_back(down);
            }
        }

        if (j - 1 >= 0) {
            if(matrix[i][j - 1] != -1){
            State<pair<int, int>>* left = new State<pair<int, int>>(make_pair(i, j - 1), s->getCost() + matrix[i][j - 1],s);
            states.push_back(left);
            allocatedStates.push_back(left);
            }
        }

        if (j + 1 <= maxCol) {
            if(matrix[i][j + 1] != -1){
            State<pair<int, int>> *right = new State<pair<int, int>>(make_pair(i, j + 1), s->getCost() + matrix[i][j + 1],s);
            states.push_back(right);
                allocatedStates.push_back(right);
            }
        }
        return states;
    }

    pair<int, int> getGoalState() {
        pair<int, int> goalStateLoc = this->goalState;
        return goalStateLoc;
    }

    string to_string(){
        string result = "";
        for(string line : matrixStr){
            result += line;
            result += "@";
        }
        //result.pop_back();
        pair<int,int> startPair = this->startState;
        result += std::to_string(startPair.first) + ',' + std::to_string
                (startPair.second) + '@';
        pair<int,int> endPair = this->goalState;
        result += std::to_string(endPair.first) + ',' + std::to_string
                (endPair.second);
        return result;
    }

    ~matrixProblem(){
        for(auto State : this->allocatedStates){
            if(State != nullptr)
                delete State;
        }
    }
};


#endif //PROJECT_MILSTONE2_MATRIXPROBLEM_H
