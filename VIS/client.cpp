
#include <iostream>
#include <string>
#include "client.h"
#include "SocketsInterface.h"

typedef struct ThreadArguments {
	SocketsInterface *ta_sockets;
	SOCKET ta_client_socket;
} THREAD_ARGUMENTS;

void *ThreadRoutine(THREAD_ARGUMENTS *arguments)
{
	if (arguments) {

		char buffer[1024 * 80] = {};
		int size = 0;
		const long EchoBufferSize = 1024 * 900;
		std::string receiveData;

		while (true)
		{
			if ((size = arguments->ta_sockets->ReceiveRequest(arguments->ta_client_socket, buffer, EchoBufferSize)) < 0) {
				arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
				printf_s("%s", "error");
				return 0;
			}
			std::string singledata = std::string(buffer, size);
			std::cout << singledata << std::endl;
			Sleep(1000);


			std::string data = "1";
			arguments->ta_sockets->SendRequest(arguments->ta_client_socket, data.c_str(), data.size());


		}
	}
	//free(thread_arguments);
	return (NULL);
}
//
//  Client application.
//
int main(int argc, char **argv)
{
	//ClientApplication application;
	//application.ProcessClientRequest();

	SocketsInterface *sockets=new SocketsInterface();
	SOCKET server_socket = sockets->CreateSocket();
	
	server_socket = sockets->BindSocket(server_socket, 5001);

	server_socket = sockets->ListenConnections(server_socket, 16);
	
	for (;;) {
		SOCKET client_socket = sockets->AcceptConnections(server_socket);
		struct ThreadArguments *thread_arguments = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments));
		if (!thread_arguments) {
			throw (std::runtime_error(std::string("insufficient memory for allocating thread argument structure")));
		}
		thread_arguments->ta_sockets = sockets;
		thread_arguments->ta_client_socket = client_socket;
		DWORD thread_id;
		if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, thread_arguments, 0, (LPDWORD)&thread_id) == NULL) {
			throw (std::runtime_error(std::string("CreateThread() failed")));
		}


	}
	return (0);
}


//
//  Class constructor for client application.
//
ClientApplication::ClientApplication(void)
{
	host_address = std::string("127.0.0.1");
	port = 1000;
	data = std::string("");
}

//
//  Process client request.
//
void ClientApplication::ProcessClientRequest(void)
{
	SocketsInterface sockets;
	char *buffer;
	data="{\"commandType\":\"init\",\"data\":[{\"cameraIp\":\"129.0.1.1\",\"cameraPass\":\"0\",\"isPersonIdentified\":true,\"isEndoscopeIdentified\":true,\"isGunIdentified\":false,\"isTransferLiquidIdentified\":false,\"isTransferClothIdentified\":false},{\"cameraIp\":\"129.0.1.1\",\"cameraPass\":\"1\",\"isPersonIdentified\":true,\"isEndoscopeIdentified\":true,\"isGunIdentified\":true,\"isTransferLiquidIdentified\":true,\"isTransferClothIdentified\":true}]}";
	int buffer_size = 1000;

	if ((buffer = (char *)malloc(buffer_size + 1)) == NULL) {
		DisplayErrorMessage(std::string("insufficient memory to allocating client request buffer"));
		return;
	}

	memset(buffer, 0, buffer_size + 1);
	data = "";
	try {
		SOCKET client_socket = sockets.CreateSocket();

		sockets.ConnectServer(client_socket,host_address, port);
		/*std::cout << "connecting to " << host_address << " at port " << port << std::endl;

		int bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
		std::cout << data << std::endl;
		Sleep(1000);
		data="{\"commandType\":\"start\",\"data\":[]}";
		bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
		std::cout << data << std::endl;
		Sleep(1000);
		data="{\"commandType\":\"takePicture\",\"data\":[{\"cameraIp\":\"129.0.1.1\",\"cameraPass\":\"0\",\"isStop\":false,\"frequency\":0,\"imageformart\":1,\"isImageDrowBorder\":true}]}";
		bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
		std::cout << data << std::endl;
		Sleep(1000);
		data="{\"commandType\":\"takePicture\",\"data\":[{\"cameraIp\":\"129.0.1.1\",\"cameraPass\":\"0\",\"isStop\":true,\"frequency\":0,\"imageformart\":1,\"isImageDrowBorder\":false}]}";
		bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
		std::cout << data << std::endl;
		Sleep(1000);
		data="{\"commandType\":\"stop\",\"data\":[]}";
		bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
		std::cout << data << std::endl;
		Sleep(1000);*/
		while (true) {
			/*int bytes_received = sockets.ReceiveRequest(client_socket, buffer, buffer_size);
			if (bytes_received < 0) {
				break;
			}
			std::cout << std::string(buffer)<<std::endl;
			preReceiveData=std::string(buffer);

			memset(buffer, 0, buffer_size + 1);*/

			sockets.SendRequest(client_socket, data.c_str(), data.size());
			Sleep(1000);

		}

		std::cout << std::endl;

		sockets.CloseSocket(client_socket);
	}
	catch (std::exception& e) {
		DisplayErrorMessage(std::string(e.what()));
	}

	free(buffer);
}


//
//  Display error message.
//
void ClientApplication::DisplayErrorMessage(const std::string& message)
{
	std::cout << "error-> " << message << std::endl;
}


