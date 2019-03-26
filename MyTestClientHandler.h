#ifndef SERVER_SIDE_CLIENTTESTHANDLER_H
#define SERVER_SIDE_CLIENTTESTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include <strings.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class ClientHandlerTest :public ClientHandler {
private:
    Solver<string , string> *_solver;
public:
    ClientHandlerTest(Solver<string , string> *_solver);

    void handleClient(int socket_number) ;

    /**
     * reading input from the client socket
     * @param socket_number
     * @return
     */
    string getClientProblem (int socket_number);

    /**
     * writing to the client socket
     * @param socket_number
     * @param output
     */
    void writeClientSolution (int socket_number , string output);

    /**
 * split the string acording to the delimiter
 * @param s
 * @param delimiter
 * @return
 */
    vector<string> split(string &s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};


#endif //SERVER_SIDE_CLIENTTESTHANDLER_H
