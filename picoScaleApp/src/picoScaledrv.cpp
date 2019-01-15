#include <string>

//EPICS includes
#include <recGbl.h>
#include <alarm.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <subRecord.h>
#include <genSubRecord.h>

//AsynPortDriver include
#include <asynPortDriver.h>


#include <picoScaledrv.h>
#include <picoScale_dataSrc.h>
#include <picoScale_Stream.h>

PicoScaledrv::PicoScaledrv(const char *portName):
	asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS,
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynDrvUserMask,// Interfaces that we implement
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask,	// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
	0, 0) /* Default priority and stack size */
{
	createParam(pos_ch0_waveformValueString, asynParamFloat64Array, &pos_ch0_waveformValue);
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
		//error
		return result;
	}

	dataSource.dataSize = getDataSize(dataSource.dataType);
	dataSource.address.channelIndex = channelindx_mbboValue;
	dataSource.address.dataSourceIndex = datasrcindx_mbboValue;
	
	streamConfig.interleavingEnabled = interleaving_boValue;
    	//streamConfig.frameAggregation = 
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	//streamConfig.frameRate = 
    	streamConfig.numberOfStreamBuffers = buffersnum_longOutValue;
        streamConfig.frameSize = dataSource.dataSize;

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
		result = receiveStreamBuffer(handle,2000,lastFrame);
		if (result != SA_SI_OK)
		    return result;
    	}

	return SA_SI_OK;	
}

unsigned int picoScale_streamPVA(genSubRecord *pgenSub){//method for streaming position/velocity/acceleration measurements from all channels
	bool lastFrame = false;

	streamConfig.interleavingEnabled = interleaving_boValue;
    	//streamConfig.frameAggregation = 
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	//streamConfig.frameRate = 
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
		result = receiveStreamBuffer(handle,2000,lastFrame);
		if (result != SA_SI_OK)
		    return result;
    	}

	return SA_SI_OK;	
}

unsigned int picoScale_streamPosition_allChannels(genSubRecord *pgenSub){//method for streaming position measurements from all (3) channels
	bool lastFrame = false;
	
	streamConfig.interleavingEnabled = interleaving_boValue;
    	//streamConfig.frameAggregation = 
    	streamConfig.streamBufferAggregation = bufferaggr_mbboValue;
    	//streamConfig.frameRate = 
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
		result = receiveStreamBuffer(handle,2000,lastFrame);
		if (result != SA_SI_OK)
		    return result;
    	}

	return SA_SI_OK;	
}

unsigned int picoScale_poll(subRecord *psub){
	
}

unsigned int  picoScale_adjust(subRecord *psub){
// activate manual adjustment phase
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_AF_ADJUSTMENT_STATE_PROP,0,0),SA_PS_ADJUSTMENT_STATE_MANUAL_ADJUST);
    if (result != SA_SI_OK)
        return result;
}

epicsRegisterFunction(picoScale_open);
epicsRegisterFunction(picoScale_close);
epicsRegisterFunction(picoScale_setFramerate);
epicsRegisterFunction(picoScale_stream);
epicsRegisterFunction(picoScale_streamPVA);
epicsRegisterFunction(picoScale_streamPosition_allChannels);
epicsRegisterFunction(picoScale_poll);
epicsRegisterFunction(picoScale_adjust);

