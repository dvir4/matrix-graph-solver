#ifndef SERVER_SIDE_CLIENTHANDLER_H
#define SERVER_SIDE_CLIENTHANDLER_H

class ClientHandler {
public:
    virtual void handleClient (int socket_number) = 0 ;
};

#endif //SERVER_SIDE_CLIENTHANDLER_H
