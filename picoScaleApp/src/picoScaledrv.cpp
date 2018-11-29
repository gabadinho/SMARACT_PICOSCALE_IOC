#include <subRecord.h>
#include <registryFunction.h>
#include <genSubRecord.h>
#include <asynPortDriver.h>
#include <picoScale_dataSrc.h>
#include <picoScaledrv.h>

#define MAX_SIGNALS		

PicoScaledrv::PicoScaledrv(const char *portName):
	asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS,
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynDrvUserMask,// Interfaces that we implement
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask,	// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1,
	/* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
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
	createParam(locator_stringOutValueString, asynParamOctet, &locator_stringOutValue);
	createParam(framerate_longOutValueString, asynParamInt32, &framerate_longOutValue);
	//createParam(frameaggr_mbboValueString, asynParamInt32, &frameaggr_mbboValue); mbbo value
	///createParam(bufferaggr_mbboValueString, asynParamInt32, &bufferaggr_mbboValue);
	//createParam(interleaving_boValueString, asynParamFloat64, &interleaving_boValue); bool value
	//createParam(channelindx_mbboValueString, asynParamInt32, &channelindx_mbboValue);mbbo value
	//createParam(datasrcindx_mbboValueString, asynParamInt32, &datasrcindx_mbboValue);mbbo value
	createParam(workingdistmin_longOutValueString, asynParamInt32, &workingdistmin_longOutValue);
	createParam(workingdistmax_longOutValueString, asynParamInt32, &workingdistmax_longOutValue);
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






