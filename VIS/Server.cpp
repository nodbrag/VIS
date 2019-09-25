
#include <iostream>
#include <string>
#include "log.h"
#include "Server.h"
#include "SocketsInterface.h"
#include "EchoService.h"


//
//  Local function prototypes.
//
void *ThreadRoutine(void *);

//
//  Sockets interface.
//
SocketsInterface Server::*sockets;

//
//  Server log.
//
Log Server::*server_log;

//
//  Class constructor for server.
//
Server::Server(const int port, const int pending_connections, const std::string& log_file_path, const bool trace_mode)
{
	this->port = port;
	this->pending_connections = pending_connections;
	this->log_file_path = log_file_path;
	this->trace_mode = trace_mode;

	sockets = new SocketsInterface();
	server_log = new Log(log_file_path);
}

//
//  Class destructor for server.
//
Server::~Server(void)
{
	sockets->~SocketsInterface();
	server_log->~Log();
}

//
//  Serve requests with a maximum number of threads.
//
void Server::ServerRequests(void)
{
	SOCKET server_socket = sockets->CreateSocket();
	
	if (trace_mode) {
		std::string trace_message = std::string("server socket created " + std::to_string(server_socket));
		server_log->WriteTraceLog(trace_message);
		printf_s("%s\n", trace_message.c_str());
	}

	server_socket = sockets->BindSocket(server_socket, port);

	if (trace_mode) {
		std::string trace_message = std::string("server socket bound to local address using server socket " + std::to_string(server_socket) + " and port number " + std::to_string(port));
		server_log->WriteTraceLog(trace_message);
		printf_s("%s\n\r", trace_message.c_str());
	}

	server_socket = sockets->ListenConnections(server_socket, pending_connections);

	if (trace_mode) {
		std::string trace_message = std::string("server socket listening to connections using server socket " + std::to_string(server_socket) + " and pending connections (backlog) " + std::to_string(pending_connections));
		server_log->WriteTraceLog(trace_message);
		printf_s("%s\n\r", trace_message.c_str());
	}

	for (;;) {
		SOCKET client_socket = sockets->AcceptConnections(server_socket);

		if (trace_mode) {
			std::string trace_message = std::string("accepted connection from client " + std::to_string(client_socket));
			server_log->WriteTraceLog(trace_message);
			printf_s("%s\n\r", trace_message.c_str());
		}
		struct ThreadArguments *thread_arguments = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments));
		if (!thread_arguments) {

			throw (std::runtime_error(std::string("insufficient memory for allocating thread argument structure")));
			server_log->WriteTraceLog("error:insufficient memory for allocating thread argument structure");
		}
		
		thread_arguments->ta_sockets = sockets;
		thread_arguments->ta_client_socket = client_socket;
		thread_arguments->ta_server_log = server_log;
		thread_arguments->ta_server_log_trace_mode = trace_mode;

		if (trace_mode) {
			std::string trace_message = std::string("thread arguments structure created for server socket " + std::to_string(server_socket));
			server_log->WriteTraceLog(trace_message);
		}

		DWORD thread_id;
		if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, thread_arguments, 0, (LPDWORD)&thread_id) == NULL) {
			throw (std::runtime_error(std::string("CreateThread() failed")));
			server_log->WriteTraceLog("error:CreateThread() failed");
		}

		if (trace_mode) {
			std::string trace_message = std::string("thread created (TID) " + std::to_string(thread_id));
			server_log->WriteTraceLog(trace_message);
			printf_s("%s\n\r", trace_message.c_str());
		}
	}
}

//
//  Thread routine.
//
void *ThreadRoutine(void *thread_arguments)
{
	if (thread_arguments) {
		EchoService echoService;
		echoService.HandleRequest(((THREAD_ARGUMENTS *)thread_arguments));
	}
	//free(thread_arguments);
	return (NULL);
}