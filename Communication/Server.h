#ifndef SERVER_SIDE_SERVER_H
#define SERVER_SIDE_SERVER_H

#include "ClientHandler.h"

// interface of servers
class Server {
public :
    /**
     * the function open the connection between mulitple client to a server
     * @param port port number
     * @param c object to call the type of the convercetion between client
     * and sever
     */
    virtual void open(int port, ClientHandler* c)=0;

//    virtual void open(int port)=0;

    /**
     * the function stops the connection between the cliens and the server .
     * the end of the connection will happend when the timeout will pass or
     * when the user will insert "end"
     */
    virtual void stop()=0;

    /**
     * distrctor of the server .
     * resonsseble to closing all the threads of the clients and the socket
     */
    virtual ~Server(){};
};


#endif //SERVER_SIDE_SERVER_H
