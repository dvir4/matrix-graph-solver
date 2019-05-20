#include <cstdio>
#include <cstdlib>
#include "ParallelServer.h"


void ParallelServer::open(int port, ClientHandler *c) {
    this->ch = c;
    struct sockaddr_in serverAddr;

    if ((_m_sockID = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == FAILD) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(_m_sockID, SOL_SOCKET, SO_REUSEADDR, &sock_val,
                   sizeof(sock_val)) == FAILD) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    //Set all bits of the padding field to 0
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    if (bind(_m_sockID, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) ==
        FAILD) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(_m_sockID, QUEUE_SIZE) == FAILD) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    this->server_thread = new std::thread(&ParallelServer::acceptClient, this);

}

void ParallelServer::stop() {
    // trying to close the sockts
    if (shutdown(_m_sockID, SHUT_RDWR) > 0) {
        perror("TcpServer->detach->shutdown 1: ");
    }
    sleep(1);
    if (close(_m_sockID) > 0) {
        perror("TcpServer->detach->close 1: ");
    }

}

void ParallelServer::acceptClient() {
    // at the first time will someone will connect will be infint time
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (setsockopt(_m_sockID, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,sizeof(timeout)) < 0)
        perror("setsockopt failed in first connection to the clint\n");
    int newSocket;
    while (1) {
        struct sockaddr_storage serverStorage;
        socklen_t addr_size = sizeof(serverStorage);

        newSocket = accept(_m_sockID, (struct sockaddr *) &serverStorage, &addr_size);

        timeval timeout1;
        timeout1.tv_sec = 0;
        timeout1.tv_usec = 0;

        if (setsockopt(newSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout1, sizeof(timeout)) < 0) {
            perror(" in timeout setsockopt failed\n");
            break;
        }

        if (newSocket == FAILD) {
            shutdown(_m_sockID, SHUT_RDWR);
            perror("Timeout in the server ");
            break;
        }

        this->pool->taskQueue(handleClientTask, newSocket, ch);

        // at the first time we will wait for a connection from a client .
        // after the first time we will change the server timer to be
        // SERVER_TIMER
        timeval timeout2;
        timeout2.tv_sec = 15;
        timeout2.tv_usec = 0;
        if (setsockopt(_m_sockID, SOL_SOCKET, SO_RCVTIMEO, (char *)
                &timeout2, sizeof(timeout2)) < 0) {
            perror("setsockopt failed in while loop\n");
            break;
        }

        if (_m_sockID == TIME_OUT) {
            perror("time has passed for the client");
            break;
        }

    }
}

ParallelServer::~ParallelServer() {
    this->server_thread->join();
    stop();
    delete this->server_thread;
    delete this->pool;
}

void ParallelServer::handleClientTask(int sockfd, ClientHandler *clientHandler) {
    clientHandler->handleClient(sockfd);
}
