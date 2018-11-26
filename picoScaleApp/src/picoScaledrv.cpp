#include <subRecord.h>
#include <registryFunction.h>
#include <genSubRecord.h>
#include <asynPortDriver.h>
#include <picoScale_dataSrc.h>
#include <picoScaledrv.h>

#define MAX_SIGNALS		

PicoScaledrv::PicoScaledrv(const char *portName):
	asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS,
	asynInt32Mask | asynUInt32DigitalMask | asynDrvUserMask,// Interfaces that we implement
	asynUInt32DigitalMask,	// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1,
	/* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
	0, 0), /* Default priority and stack size */
	)
{
	createParam()
}

unsigned int picoScale_open(psub)
	struct subRecord  *psub;
{
    	SA_SI_Handle handle;
    	return(SA_SI_Open(&handle, ))
}


picoScale_close(){

}

picoScale_stream(){

}

picoScale_streamPVA(){

}

picoScale_poll(){

}

picoScale_adjust(){

}






