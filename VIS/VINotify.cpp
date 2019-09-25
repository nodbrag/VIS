#include "VINotify.h"
#include "VIBase.h";
#include "VIBussiness.h";

VINotify::VINotify(void)
{
}


VINotify::~VINotify(void)
{
}

void VINotify::ThreadRunnableHandleRequest( THREAD_ARGUMENTS * thread_arguments )
{
	if (thread_arguments) {
		VIBase *viHand=new VIBussiness();
		viHand->log=thread_arguments->ta_server_log;
		viHand->currentThread=thread_arguments;
		switch (thread_arguments->opType)
		{
		case 0:
			viHand->log->WriteTraceLog("notify-> initializeData");
			VIBussiness::visetting=thread_arguments->visetting;
			VIBussiness::tankmap=thread_arguments->tankmap;
			VIBussiness::cgvector=thread_arguments->cgvector;
			VIBussiness::vsparms = thread_arguments->vsparms;
			VIBussiness::tankgroupids = thread_arguments->groupids;
			VIBussiness::flowtypemap = thread_arguments->flowtypemap;
			viHand->InitializeData(thread_arguments->camerasMap);

			break;
		case 1:
			viHand->log->WriteTraceLog("notify-> startWork ");
			viHand->StartWork();
			break;
		case 2:
			viHand->log->WriteTraceLog("notify-> stopWork");
			viHand->StopWork();
			break;
		case 3:
			viHand->log->WriteTraceLog("notify-> StartTakePhoto");
			viHand->StartTakePhoto(thread_arguments->takePhotoParms);
			break;
		case 4:
			viHand->log->WriteTraceLog("notify-> StopTakePhoto");
			viHand->StopTakePhoto();
			break;
		case 5:
			viHand->log->WriteTraceLog("notify-> test");
			viHand->SetSimulated(thread_arguments->simulatedData);
			break;
		default:
			break;
		}
		free(thread_arguments);
		delete viHand;
	}
}





