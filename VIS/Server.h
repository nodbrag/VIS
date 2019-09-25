#ifndef __SERVER_H
#define __SERVER_H

#include <string>
#include "ThreadArguments.h";
//
//  Server class.
//
class Server {
public:
        Server(const int, const int, const std::string&, const bool);
       ~Server(void);
        void ServerRequests(void);

private:
        int port;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;
        SocketsInterface *sockets;
        Log *server_log;
};

#endif // __SERVER_H

