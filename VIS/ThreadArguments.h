
//
//  Thread arguments structure and type.
//
#ifndef _Argument_H
#define _Argument_H

#include <vector>
#include <map>
#include "SocketsInterface.h"
#include "Log.h"
#include "CameraMap.h"
#include "TakePhotoParms.h"
#include "SimulatedData.h"
#include "VISetting.h"
#include "Tank.h"
#include "CameraGroup.h"
#include "VSParms.h"


  typedef struct ThreadArguments {
        SocketsInterface *ta_sockets;
        SOCKET ta_client_socket;
        Log *ta_server_log;
        bool ta_server_log_trace_mode;
		TakePhotoParms *takePhotoParms;
		SimulatedData *simulatedData;
		VISetting * visetting;
		map<string,std::vector<CameraMap*>> * camerasMap;
		map<std::string,vector<Tank *>> * tankmap;
		std::vector<CameraGroup*> * cgvector;
		std::vector<string> *groupids;
		std::map<string, vector<std::string>> *flowtypemap;
		VSParms *vsparms;
		int opType;
   } THREAD_ARGUMENTS;

#endif
