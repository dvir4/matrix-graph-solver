#include <cstring>
#include "MyTestClientHandler.h"

ClientHandlerTest::ClientHandlerTest(Solver<string, string> *_solver) : _solver(_solver) {}

void ClientHandlerTest::handleClient(int socket_number) {
    string user_prob = getClientProblem(socket_number);
    user_prob.pop_back();
    // cutting the new line in the end of the string
    while (user_prob != "end") {
        string result = (this->_solver)->Solve(user_prob) + "\n";
        writeClientSolution(socket_number, result);
        user_prob = getClientProblem(socket_number);
        user_prob.pop_back();
    }
}

void ClientHandlerTest::writeClientSolution(int socket_number, string output) {
    char buffer[1000];
    bzero(buffer, 1000);
    strcpy(buffer, output.c_str());

    /* send message to the server */

    ssize_t n = write(socket_number, buffer, strlen(buffer));

    if (n < 0) {
        throw "client error";
        exit(1);
    }
}

string ClientHandlerTest::getClientProblem(int socket_number) {
    // reading from client
    char buffer[256];

    /* If connection is established then start communicating */
    bzero(buffer, 256);
    int n = read(socket_number, buffer, 255);

    if (n < 0) {
        perror("ERROR reading from socket");
        throw 0; // cant read socket
    }
    return buffer;
}
