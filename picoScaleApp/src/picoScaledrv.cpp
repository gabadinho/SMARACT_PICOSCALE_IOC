#include <iocsh.h>
#include <epicsExport.h>
#include <asynPortDriver.h>
#include <picoScale_dataSrc.h>

static const char *driverName = "picoScaledrv";

#define 

class PicoScaledrv : public asynPortDriver {
	public:
		PicoScaledrv(const char *portName, int boardNum);
		virtual asynStatus readFloat64Array(asynUser *pasynUser, epicsFloat64 *value, size_t nElements, size_t *nIn);
		virtual asynStatus writeFloat64Array(asynUser *pasynUser, epicsFloat64 *value, size_t nElements);
		
	

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






