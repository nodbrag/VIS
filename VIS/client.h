
#ifndef __CLIENT_APPLICATION_H
#define __CLIENT_APPLICATION_H

#include <string>

//
//  Client application class.
//
class ClientApplication {
public:
        ClientApplication(void);
        void ProcessClientRequest(void);

private:
        void DisplayErrorMessage(const std::string&);
private:
        std::string host_address;
        int port;
        std::string data;
		std::string preReceiveData;
};

#endif // __CLIENT_APPLICATION_H
