#ifndef SERVER_SIDE_PARALLELSERVER_H
#define SERVER_SIDE_PARALLELSERVER_H

#include "Server.h"
#include "ThreadPool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <thread>

#define TIME_OUT -5
#define FAILD -1
#define QUEUE_SIZE 50

const int sock_val = 1;

class ParallelServer : public Server {
private:
    ThreadPool *pool;
    ClientHandler *ch;
    std::thread *server_thread;
    int _m_sockID;
    static void handleClientTask(int sockfd, ClientHandler* clientHandler);

public :

    ParallelServer() {
        // number of the parallel threads in the pool
        pool = new ThreadPool(10);
    }

    /**
     * the function open the connection between mulitple client to a server
     * @param port port number
     * @param c object to call the type of the convercetion between client
     * and sever
     */
    void open(int port, ClientHandler *c);

    /**
     * the function stops the connection between the cliens and the server .
     * the end of the connection will happend when the timeout will pass or
     * when the user will insert "end"
     */
    void stop();

    void acceptClient();

    ~ParallelServer();
};


#endif //SERVER_SIDE_PALLELSERVER_H
