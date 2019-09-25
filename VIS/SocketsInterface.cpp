
#include <string>
#include <winsock.h>
#include "SocketsInterface.h"
#pragma comment(lib,"ws2_32.lib")
//
//  Class constructor for sockets interface.
//
SocketsInterface::SocketsInterface(void)
{
    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
        throw (std::runtime_error(std::string("WSAStartup() failed")));
    }
}

//
//  Class destructor for sockets interface.
//
SocketsInterface::~SocketsInterface(void)
{
    WSACleanup();
}

//
//  Create a socket.
//
SOCKET SocketsInterface::CreateSocket(void)
{
    SOCKET client_socket;
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw (std::runtime_error(std::string("socket() failed")));
    }
    return (client_socket);
}

//
//  Connect to server using client socket, IP address and port number.
//
SOCKET SocketsInterface::ConnectServer(SOCKET client_socket, const std::string& host_address, const int port)
{
    if (!port) {
        throw (std::runtime_error(std::string("invalid port number")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(host_address.c_str());
    socket_address.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("connect() failed")));
    }
    return (client_socket);
}

//
//  Bind socket to local address using server socket and port number.
//
SOCKET SocketsInterface::BindSocket(SOCKET server_socket, const int port)
{
    if (!port) {
        throw (std::runtime_error(std::string("invalid port number")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("bind() failed")));
    }
    return (server_socket);
}

//
//  Listen for connections using server socket and pending connections (limit).
//
SOCKET SocketsInterface::ListenConnections(SOCKET server_socket, int pending_connections)
{
    if (pending_connections < 1) {
        pending_connections = SOMAXCONN;
    }
	
	//int nSendBuf= 100 * 1024 * 1024;//ÉèÖÃÎª32M
	//setsockopt(server_socket,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));

	int rcvbuf = 100 * 1024 * 1024;
	setsockopt(server_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&rcvbuf, sizeof(int));

    if (listen(server_socket, pending_connections) < 0) {
        throw (std::runtime_error(std::string("listen() failed")));
    }
    return (server_socket);
}

//
//  Accept a connection using server socket returning a client socket.
//
SOCKET SocketsInterface::AcceptConnections(const SOCKET server_socket)
{
    SOCKET client_socket;
    struct sockaddr_in client_address;
    int client_address_length = sizeof(client_address);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length)) < 0) {
        throw (std::runtime_error(std::string("accept() failed")));
    }
    return client_socket;
}

//
//  Send request using client socket, buffer and buffer size.
//
int SocketsInterface::SendRequest(const SOCKET client_socket, const char *buffer, const int buffer_size)
{
    int send_size = 0;

    if (client_socket) {
        send_size = send(client_socket, buffer, buffer_size, 0);
    }
    return (send_size);
}

//
//  Receive request using client socket, buffer and buffer size.
//
int SocketsInterface::ReceiveRequest(const SOCKET client_socket, char *buffer, const int buffer_size)
{
    int receive_size = 0;

    if (client_socket) {
        memset(buffer, 0, buffer_size);
        receive_size = recv(client_socket, buffer, buffer_size, 0);
    }
    return (receive_size);
}

//
//  Close socket.
//
void SocketsInterface::CloseSocket(SOCKET socket)
{
    if (socket) {
        closesocket(socket);
    }
}
