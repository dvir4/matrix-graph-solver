#ifndef SERVER_SIDE_STRINGREVERSER_H
#define SERVER_SIDE_STRINGREVERSER_H

#include "Solver.h"
#include <string>

class StringReverser : public Solver<string, string> {
public:
    /**
     * @param s - string object
     * @return a reversed string of the given string
     */
    string Solve(string s){
        int n = s.length();
        string result = s;

        for(int i = 0; i < n/2; i++){
            swap(result[i], result[n - i - 1]);
        }

        return result;
    }
};


#endif //SERVER_SIDE_STRINGREVERSER_H
