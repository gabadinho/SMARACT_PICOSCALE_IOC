#include <string>

//EPICS includes
#include <recGbl.h>
#include <alarm.h>
#include <epicsExport.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <genSubRecord.h>

//AsynPortDriver include
#include <asynPortDriver.h>

//SmarAct includes
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

#include <picoScaledrv.h>

PicoScaledrv::PicoScaledrv(const char *portName):
	asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS,
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynDrvUserMask,// Interfaces that we implement
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask,	// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
	0, 0) /* Default priority and stack size */
{
	createParam(vel_ch0_waveformValueString, asynParamFloat64Array, &vel_ch0_waveformValue);
	createParam(acc_ch0_waveformValueString, asynParamFloat64Array, &acc_ch0_waveformValue);
	createParam(swraw_ch0_analogInValueString, asynParamFloat64, &swraw_ch0_analogInValue);
	createParam(s2wraw_ch0_analogInValueString, asynParamFloat64, &s2wraw_ch0_analogInValue);
	createParam(swquality_ch0_analogInValueString, asynParamFloat64, &swquality_ch0_analogInValue);
	createParam(s2wquality_ch0_analogInValueString, asynParamFloat64, &s2wquality_ch0_analogInValue);
	createParam(cntrZero_ch0_analogInValueString, asynParamFloat64, &cntrZero_ch0_analogInValue);
	createParam(cntrOne_ch0_analogInValueString, asynParamFloat64, &cntrOne_ch0_analogInValue);
	createParam(envtemp_ch0_analogInValueString, asynParamFloat64, &envtemp_ch0_analogInValue);
	createParam(envHum_ch0_analogInValueString, asynParamFloat64, &envHum_ch0_analogInValue);
	createParam(envPress_ch0_analogInValueString, asynParamFloat64, &envPress_ch0_analogInValue);
	createParam(gpioAdc0_ch0_analogInValueString, asynParamFloat64, &gpioAdc0_ch0_analogInValue);
	createParam(gpioAdc1_ch0_analogInValueString, asynParamFloat64, &gpioAdc1_ch0_analogInValue);
	createParam(gpioAdc2_ch0_analogInValueString, asynParamFloat64, &gpioAdc2_ch0_analogInValue);
	createParam(calcSys0_ch0_analogInValueString, asynParamFloat64, &calcSys0_ch0_analogInValue);
	createParam(calcSys1_ch0_analogInValueString, asynParamFloat64, &calcSys1_ch0_analogInValue);
	createParam(calcSys2_ch0_analogInValueString, asynParamFloat64, &calcSys2_ch0_analogInValue);
	createParam(calcSys3_ch0_analogInValueString, asynParamFloat64, &calcSys3_ch0_analogInValue);
	createParam(calcSys4_ch0_analogInValueString, asynParamFloat64, &calcSys4_ch0_analogInValue);
	createParam(calcSys5_ch0_analogInValueString, asynParamFloat64, &calcSys5_ch0_analogInValue);
	createParam(calcSys6_ch0_analogInValueString, asynParamFloat64, &calcSys6_ch0_analogInValue);
	createParam(calcSys7_ch0_analogInValueString, asynParamFloat64, &calcSys7_ch0_analogInValue);
	createParam(pos_ch1_waveformValueString, asynParamFloat64Array, &pos_ch1_waveformValue);
	createParam(vel_ch1_waveformValueString, asynParamFloat64Array, &vel_ch1_waveformValue);
	createParam(acc_ch1_waveformValueString, asynParamFloat64Array, &acc_ch1_waveformValue);
	createParam(swraw_ch1_analogInValueString, asynParamFloat64, &swraw_ch1_analogInValue);
	createParam(s2wraw_ch1_analogInValueString, asynParamFloat64, &s2wraw_ch1_analogInValue);
	createParam(swquality_ch1_analogInValueString, asynParamFloat64, &swquality_ch1_analogInValue);
	createParam(s2wquality_ch1_analogInValueString, asynParamFloat64, &s2wquality_ch1_analogInValue);
	createParam(pos_ch2_waveformValueString, asynParamFloat64Array, &pos_ch2_waveformValue);
	createParam(vel_ch2_waveformValueString, asynParamFloat64Array, &vel_ch2_waveformValue);
	createParam(acc_ch2_waveformValueString, asynParamFloat64Array, &acc_ch2_waveformValue);
	createParam(swraw_ch2_analogInValueString, asynParamFloat64, &swraw_ch2_analogInValue);
	createParam(s2wraw_ch2_analogInValueString, asynParamFloat64, &s2wraw_ch2_analogInValue);
	createParam(swquality_ch2_analogInValueString, asynParamFloat64, &swquality_ch2_analogInValue);
	createParam(s2wquality_ch2_analogInValueString, asynParamFloat64, &s2wquality_ch2_analogInValue);
	createParam(ip_stringOutValueString, asynParamOctet, &ip_stringOutValue);
	createParam(framerate_longOutValueString, asynParamInt32, &framerate_longOutValue);
	createParam(frameaggr_mbboValueString, asynParamInt32, &frameaggr_mbboValue);
	createParam(bufferaggr_mbboValueString, asynParamInt32, &bufferaggr_mbboValue);
	createParam(buffersnum_longOutValueString, asynParamInt32, &buffersnum_longOutValue);
	createParam(interleaving_boValueString, asynParamInt32, &interleaving_boValue);
	createParam(channelindx_mbboValueString, asynParamInt32, &channelindx_mbboValue);
	createParam(datasrcindx_mbboValueString, asynParamInt32, &datasrcindx_mbboValue);
	createParam(workingdistmin_longOutValueString, asynParamInt32, &workingdistmin_longOutValue);
	createParam(workingdistmax_longOutValueString, asynParamInt32, &workingdistmax_longOutValue);
}

/*
struct DataSourceDescription_t {
    int32_t componentID;
    int32_t componentIndex;
    int32_t dataSourceType;
};
*/

struct DataSourceAddress_t {
    uint8_t channelIndex;
    uint8_t dataSourceIndex;
};

struct DataSource_t {
    DataSourceAddress_t address;
    int32_t dataType;
    int32_t dataSize;
};

struct DataSourceData_t {
    vector<VariantValue> data;
};

/*
struct StreamData_t {
    vector<DataSourceData_t> dataSource;
};*/

struct StreamConfig_t {
    //vector<DataSource_t> enabledDataSources;
    //int32_t frameSize;
    bool interleavingEnabled;
    int32_t frameAggregation;
    int32_t streamBufferAggregation;
    int32_t frameRate;
    int32_t numberOfStreamBuffers;
};


// A union to store different types in one variable
union VariantValue
{
    uint8_t u8value;
    int8_t i8value;
    uint16_t u16value;
    int16_t i16value;
    uint32_t u32value;
    int32_t i32value;
    uint64_t u48value;
    int64_t i48value;
    uint64_t u64value;
    int64_t i64value;
    float f32value;
    double f64value;
};

int32_t getDataSize(int32_t dataType)
{
    switch (dataType)
    {
        case SA_SI_INT8_DTYPE:
        case SA_SI_UINT8_DTYPE:
            return 1;
            break;
        case SA_SI_INT16_DTYPE:
        case SA_SI_UINT16_DTYPE:
            return 2;
            break;
        case SA_SI_INT32_DTYPE:
        case SA_SI_UINT32_DTYPE:
        case SA_SI_FLOAT32_DTYPE:
            return 4;
            break;
        case SA_SI_INT48_DTYPE:
        case SA_SI_UINT48_DTYPE:
            // 48-bit values are extended to 64-bit values by default
        case SA_SI_INT64_DTYPE:
        case SA_SI_UINT64_DTYPE:
        case SA_SI_FLOAT64_DTYPE:
            return 8;
            break;
    }
    return 0;   // shouldn't happen
}

unsigned int configureStream(SA_SI_Handle handle)
{
    // prepare stream data container for received data
    //streamData.dataSource.resize(streamConfig.enabledDataSources.size());
    // configure frame aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_AGGREGATION_PROP,0,0),streamConfig.frameAggregation);
    if (result != SA_SI_OK){
        return result;
    }
    // configure frame rate
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0),streamConfig.frameRate);
    if (result != SA_SI_OK){
	 return result;
    }
    // configure stream buffer aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFER_AGGREGATION_PROP,0,0),streamConfig.streamBufferAggregation);
    if (result != SA_SI_OK){
        return result;
    }
    // configure interleaving
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFERS_INTERLEAVED_PROP,0,0),streamConfig.interleavingEnabled);
    if (result != SA_SI_OK){
	   return result;
    }
    // configure number of stream buffers
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_NUMBER_OF_STREAMBUFFERS_PROP,0,0),streamConfig.numberOfStreamBuffers);
    if (result != SA_SI_OK){
        return result;
    }
    return SA_SI_OK;
}

unsigned int receiveStreamBuffer(SA_SI_Handle handle, unsigned int timeout, bool &lastFrame, vector<int32_t> datasrcs_dataSizes)
{
    SA_SI_Event ev;
    unsigned int result = SA_SI_WaitForEvent(handle,&ev,timeout);
    if (result != SA_SI_OK)
        return result;
    if (ev.type == SA_SI_STREAMBUFFER_READY_EVENT)
    {
        // get buffer data
        //const SA_SI_DataBuffer *pBuffer;
        result = SA_SI_AcquireBuffer(handle,ev.bufferId,&pBuffer);
        if (result != SA_SI_OK)
            return result;
        processBuffer(pBuffer, datasrcs_dataSizes);
        if (pBuffer->info.flags & SA_SI_STREAM_END_FLAG)
            lastFrame = true;
        result = SA_SI_ReleaseBuffer(handle,ev.bufferId);
        if (result != SA_SI_OK)
            return result;
    }
    else
    {
        cout << "Received unexpected event type: " << ev.type << " (parameter: " << ev.devEventParameter << ")" << endl;
        return SA_SI_OTHER_ERROR;
    }
    return SA_SI_OK;
}

void processBuffer(const SA_SI_DataBuffer *buffer, vector<int32_t> datasrcs_dataSizes, int32_t frameSize)
{
    //FILE *fp;
    //fp = fopen("picoScale_positionMeasr.txt", "a");
    // Each buffer holds as many frames as we have defined by the stream
    // buffer aggregation.
    // The structure of the buffer depends on whether we use interleaving
    // or not and which data sources were enabled for streaming. In this
    // case we've enabled a position data source and a GPIO ADC.
    if (streamConfig.interleavingEnabled)
    {
        // The interleaved buffer structure is:
        //                    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        // buffer->data[0]: |            position           |  GPIO |            position           |  GPIO | ...
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        //                  |                frame 0                |                frame 1                |
        // The frame size is 10. In each frame the offset for the position is 0 and the offset
        // for the GPIO ADC is 8.
        // Since we use interleaving there is only one pointer
        // (buffer->data[0]) that points to the frames.
        for (unsigned int frame = 0; frame<buffer->info.numberOfFrames; frame++)
        {
            int32_t offset = 0;
            for (size_t dataSource=0; dataSource < buffer->info.numberOfSources; dataSource++)
            {
                void *dataSourceValue = &buffer->data[0][frame*frameSize + offset];
                offset += datasrcs_dataSizes[dataSource];
            }
        }
    }
    else // non-interleaving
    {
        // The non-interleaved buffer structure is:
        //                    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        // buffer->data[0]: |            position           |            position           | ...
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        //                  |            frame 0            |            frame 1            |
        //                    0   1   2   3
        //                  +---+---+---+---+---
        // buffer->data[1]: |  GPIO |  GPIO | ...
        //                  +---+---+---+---+---
        //                  |frame 0|frame 1|
        // There is a separate pointer for each enabled data source. In this case
        // buffer->data[0] has a frame size of 8 and buffer->data[1] has a frame
        // size of 2.
	//long int var = 0;	
        for (size_t dataSource = 0; dataSource < buffer->info.numberOfSources; dataSource++)
        {
            for (unsigned int frame = 0; frame < buffer->info.numberOfFrames; frame++)
	    {
		//fprintf(fp, "%li\n", var);
		//fputc(((int) buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize]), fp);
                void *dataSourceValue = &buffer->data[dataSource][frame*datasrcs_dataSizes[dataSource]];
            }
        }
	//fclose(fp);
    }
    // Note: The following code line is an example how it should *not* be
    // implemented. Printing to standard out is a relatively time consuming
    // operation and should be avoided at this place. At low data rates it
    // might work, but especially at high data rates the PicoScale generates
    // data faster than the host can process them, very likely leading to
    // a buffer overflow error!
    //cout << "Received " << buffer->info.numberOfFrames << " frames." << endl;
}

unsigned int picoScale_open(struct subRecord  *psub)
{
	result = (SA_SI_Open(&handle, ip_stringOutValue),"");

	if (result != SA_SI_OK)
    	{
		// = "Could not connect to device. Error " + std::to_string(result);
		return 1;
    	}
	else return result;
}

unsigned int picoScale_close(struct subRecord *psub)
{
	result = SA_SI_Close(handle);
	
	if (result != SA_SI_OK){
		//error
		return 1;
    	}
	else return result;
}

unsigned int picoScale_setFramerate(struct subRecord *psub)
{
	streamConfig.frameRate = (int32_t) psub->a;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0), streamConfig.frameRate);
	
	if (result != SA_SI_OK){
		//error
		return 1;
    	}
	
	double value;
	result = SA_SI_GetProperty_f64(handle, SA_SI_EPK(SA_SI_PRECISE_FRAME_RATE_PROP,0,0),&value,0); //the real operation framerate set by picoScale
    	
	if (result != SA_SI_OK){
		//error
        	return 1;
    	}

	setIntegerParam(framerate_longOutValue, value);
	streamConfig.frameRate = value;

	callParamCallbacks();
	
	//frame aggregation based on framerate accordingly to the Programming guide
	switch(value){
		case 1:
		case 2:
		case 4:
		case 9:
		case 19:
		case 38:
			streamConfig.frameAggregation = (int32_t) 1;
		break;
		case 76:
			streamConfig.frameAggregation = (int32_t) 1;
		break;
		case 152:
			streamConfig.frameAggregation = (int32_t) 4;
		break;
		case 305:
			streamConfig.frameAggregation = (int32_t) 8;
		break;
		case 610:
			streamConfig.frameAggregation = (int32_t) 16;
		break;
		case 1.22:
			streamConfig.frameAggregation = (int32_t) 32;
		break;
		case 2.44:
			streamConfig.frameAggregation = (int32_t) 64;
		break;
		case 4.88:
			streamConfig.frameAggregation = (int32_t) 128;
		break;
		case 9.77:
			streamConfig.frameAggregation = (int32_t) 256;
		break;
		case 19.53:
			streamConfig.frameAggregation = (int32_t) 512;
		break;
		case 625:
		case 312.5:
		case 156.25:
		case 78.13:
		case 39.06:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
		case 10:
		case 5:
		case 2.5:
		case 1.25:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
	}
	return result;
}

unsigned int picoScale_stream(genSubRecord *pgenSub){ //method for streaming a single datasource. Interleaved mode is true here, by default
	DataSource_t dataSource;
	bool lastFrame = false;

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, channelindx_mbboValue, datasrcindx_mbboValue),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	dataSource.dataSize = getDataSize(dataSource.dataType);
	dataSource.address.channelIndex = channelindx_mbboValue;
	dataSource.address.dataSourceIndex = datasrcindx_mbboValue;
	
	streamConfig.interleavingEnabled = interleaving_boValue;
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	streamConfig.numberOfStreamBuffers = buffersnum_longOutValue;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = configureStream(handle);
    	if (result != SA_SI_OK){
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}	
	
	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle,2000,lastFrame, new vector<int32_t>[dataSource.dataSize]);
		if (result != SA_SI_OK)
		    return result;
    	}
	
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK)
        	return result;

	return SA_SI_OK;	
}

unsigned int picoScale_streamPVA_allChannels(genSubRecord *pgenSub){//method for streaming position/velocity/acceleration measurements from all channels
	bool lastFrame = false;

	streamConfig.interleavingEnabled = interleaving_boValue;
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	streamConfig.numberOfStreamBuffers = buffersnum_longOutValue;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}

	result = configureStream(handle);
    	if (result != SA_SI_OK){
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}	
	
	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle,2000,lastFrame, streamPVA_allchannels_datasrcs_sizes);
		if (result != SA_SI_OK)
		    return result;
    	}

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK)
        	return result;

	return SA_SI_OK;	
}

unsigned int picoScale_streamPosition_allChannels(genSubRecord *pgenSub){//method for streaming position measurements from all (3) channels
	DataSource_t dataSource;	
	bool lastFrame = false;
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, channelindx_mbboValue, datasrcindx_mbboValue),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	streamConfig.interleavingEnabled = interleaving_boValue;
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	streamConfig.numberOfStreamBuffers = buffersnum_longOutValue;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}

	result = configureStream(handle);
    	if (result != SA_SI_OK){
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
        	return result;
	}	
	
	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle,2000,lastFrame, streamPosition_allchannels_datasrcs_sizes);
		if (result != SA_SI_OK)
		    return result;
    	}
	
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK)
        	return result;

	return SA_SI_OK;	
}

unsigned int picoScale_poll(subRecord *psub){
	return SA_SI_OK;
}

unsigned int picoScale_adjust(subRecord *psub){
// activate manual adjustment phase
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_AF_ADJUSTMENT_STATE_PROP,0,0),SA_PS_ADJUSTMENT_STATE_MANUAL_ADJUST);
    	if (result != SA_SI_OK)
        	return result;
    
	return SA_SI_OK;
}

//--- Driver function
extern "C" void PicoScaleCreateDriver(const char *portName){
	picoScaledrv = new PicoScaledrv(portName);
	return(asynSuccess);
}

static const iocshArg configArg = { "Port name", iocshArgString};
static const iocshArg * const configArgs[] = {&configArg};
static const iocshFuncDef configFuncDef = {"PicoScaleCreateDriver", 1, configArgs};

static void configCallFunc(const iocshArgBuf *args){
	PicoScaleCreateDriver(args[0].sval);
}

void drvPicoScaleRegister(void){
	iocshRegister(&configFuncDef,configCallFunc);
}

extern "C" {
	epicsExportRegistrar(drvPicoScaleRegister);
}
//---

//--- Initializing routine
extern "C" void PicoScaleInitializingRoutinesRun(){ //Should be called from st.cmd script before calling 'PicoScaleCreateDriver(portName)'. This procedure asks PicoScale for each datasource type; in this
						    //way, it's possible to determine the frame's sizes of streams and, also, distinguish each datasource in a stream in interleaved mode
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 0),&dataSourceP0.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 1),&dataSourceV0.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 2),&dataSourceA0.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 0),&dataSourceP1.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 1),&dataSourceV1.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 2),&dataSourceA1.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 0),&dataSourceP2.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 1),&dataSourceV2.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 2),&dataSourceA2.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}

	streamPVA_allchannels_datasrcs_sizes = {getDataSize(dataSourceP0.dataType), getDataSize(dataSourceV0.dataType), getDataSize(dataSourceA0.dataType),
						getDataSize(dataSourceP1.dataType), getDataSize(dataSourceV1.dataType), getDataSize(dataSourceA1.dataType), 							getDataSize(dataSourceP2.dataType), getDataSize(dataSourceV2.dataType), getDataSize(dataSourceA2.dataType)};

	streamPosition_allchannels_datasrcs_sizes = {getDataSize(dataSourceP0.dataType), getDataSize(dataSourceP1.dataType), getDataSize(dataSourceP2.dataType)};

	for(int i=0; i<streamPVA_allchannels_datasrcs_sizes.size(); i++){
		streamPVA_allchannels_frame_size += streamPVA_allchannels_datasrcs_sizes[i];	
	}
	
	for(int i=0; i<streamPosition_allchannels_frame_sizes.size(); i++){
		streamPosition_allchannels_frame_size += streamPosition_allchannels_datasrcs_sizes[i];	
	}

	return(asynSuccess);
}

//static const iocshArg configArg = { "Port name", iocshArgString};
//static const iocshArg * const configArgs[] = {&configArg};
static const iocshFuncDef configFuncDef = {"PicoScaleInitializingRoutinesRun"};//, 1, configArgs};

static void configCallFunc(const iocshArgBuf *args){
	PicoScaleInitializingRoutinesRun();
}

void initPicoScaleRegister(void){
	iocshRegister(&configFuncDef,configCallFunc);
}

extern "C" {
	epicsExportRegistrar(initPicoScaleRegister);
}
//---

epicsRegisterFunction(picoScale_open);
epicsRegisterFunction(picoScale_close);
epicsRegisterFunction(picoScale_setFramerate);
epicsRegisterFunction(picoScale_stream);
epicsRegisterFunction(picoScale_streamPVA_allChannels);
epicsRegisterFunction(picoScale_streamPosition_allChannels);
epicsRegisterFunction(picoScale_poll);
epicsRegisterFunction(picoScale_adjust);

