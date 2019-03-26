#ifndef SERVER_SIDE_MYCLIENTHANDLER_H
#define SERVER_SIDE_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "Searchable.h"
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include "CacheManager.h"
#include "convertor.h"

using namespace std;

template<class problem, class solution>
class MyClientHandler : public ClientHandler {
private:
    Solver<problem, solution> *_solver;
    CacheManager<problem, solution> *_cache_manger;
    convertor<problem, solution> *objectConvertor;

public:

    MyClientHandler(Solver<problem, solution> *solver,
                    CacheManager<problem, solution> *c_m,
                    convertor<problem, solution> *objectConvertor) {
        this->_solver = solver;
        this->_cache_manger = c_m;
        this->objectConvertor = objectConvertor;
    }


    void handleClient(int socket_number) {
        vector<string> matrix;
        stringstream ss;
        do {
            string matrix_line = getClientProblem(socket_number);
            ss << matrix_line;
        } while (ss.str().substr(ss.str().length() - 4) != "end\n");

        string readLineFromSS;
        while (std::getline(ss, readLineFromSS)) {
            matrix.push_back(readLineFromSS);
        }
        matrix.pop_back();

        problem p = objectConvertor->stringToProblem(matrix);

        if (this->_cache_manger->isSolutionExists(p)) {
//            cout << "found solution" << endl;
            solution s = this->_cache_manger->getSolution(p);
            writeClientSolution(socket_number, s);
//            cout << "found the solution in the file , close the clint" << endl;
        } else {
            solution s = (this->_solver)->Solve(p);// + "\n";
            this->_cache_manger->addSolution(p, s);
            writeClientSolution(socket_number, s);

//            cout << "didn't found the solution in the file ,close the clint" <<endl;
        }
    }

    /**
     * reading input from the client socket
     * @param socket_number
     * @return
     */
    string getClientProblem(int socket_number) {
        // reading from client
        char buffer[256];

        /* If connection is established then start communicating */
        bzero(buffer, 256);
        int n = read(socket_number, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            throw 0; // cant read socket
        }
//        cout << "the input is: " << buffer << endl;

        return std::string(buffer);
    }

    /**
     * writing to the client socket
     * @param socket_number
     * @param output
     */
    void writeClientSolution(int socket_number, string output) {
//        char buffer[1000];
//        bzero(buffer, 1000);
//        strcpy(buffer, output.c_str());

        /* send message to the server */
//        ssize_t n = write(socket_number, output.c_str(), output.length());
//        cout << buffer << endl;
//        if (n < 0) {
//            throw "client error";
//            exit(1);
//        }
        long check;
        check = ::send(socket_number, output.c_str(), output.length(), 0);
        if (check < 0) {
            throw "Client Error";
        }
    }

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

#endif //SERVER_SIDE_MYCLIENTHANDLER_H
