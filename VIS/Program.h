#pragma once
#include <string>

const int DefaultPort = 16000;
const int DefaultPendingConnectionsLimit = 16;
const int DefaultThreadLimit = 32767;

class Program
{
public:
	 Program(void);
	~Program(void);
	 void ProcessServerRequests(void);
private:
     void WriteFatalLogMessage(const std::string&);
public:
     int port;
     int pending_connections;
     std::string log_file_path;
     bool trace_mode;
};

