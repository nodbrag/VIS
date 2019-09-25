
#include "Program.h"
#include "log.h"
#include "Server.h"
#include "Common.h"
#include "date.h"
#include "XmlConfig.h"
#include "date.h"
#include <Windows.h>
#include "FileHelper.h"
#include "FFmpegDecoder.h"
#include "Md5Encode.h"
#include "pecode/PEncode.h"


int main(int argc, char **argv)
{
	Program application;
	application.ProcessServerRequests();
	return (0);
}

Program::Program(void)
{
	
	port = DefaultPort;
	pending_connections = DefaultPendingConnectionsLimit;
	trace_mode = false;
}


Program::~Program(void)
{

}


void Program::ProcessServerRequests(void){
	try {
		
		/*std::string src = "123456";
		Md5Encode encode_obj;

		std::string ret = encode_obj.Encode(src);
		std::cout << "info: " << src.c_str() << std::endl;
		std::cout << "md5: " << ret.c_str() << std::endl;*/
		PEncode pecode;
		bool check=pecode.checkPermission("vis");
		if (!check)
		{
			printf("%s", std::string("没有权限").c_str());
			system("pause");
		}

		port=1000;
		//port = 5001;
		log_file_path= Common::GetLogPath();
		trace_mode=true;
		FileHelper filehelper;
		if (!filehelper.checkFolderExist(log_file_path)) {
			filehelper.createDirectory(log_file_path);
		}
		Server server = Server(port, pending_connections, log_file_path, trace_mode);
		server.ServerRequests();
	}
	catch (std::exception& e) {
		printf("%s", std::string(e.what()).c_str());
		std::string exception_message = std::string("error-> " + std::string(e.what()));
		WriteFatalLogMessage(exception_message);
	}
}

//
//  Write fatal log message to log file.
//
void Program::WriteFatalLogMessage(const std::string& message)
{
	Log log = Log(log_file_path);
	log.WriteFatalLog(message);
}
