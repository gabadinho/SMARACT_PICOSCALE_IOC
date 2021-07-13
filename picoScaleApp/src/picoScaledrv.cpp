/*____________________________________________________________________________________________________________________________________
|	Driver support for SmarAct PicoScale interferometer developed with AsynPortDriver module from asyn/SynApps                    |
|	Brazilian Synchroton Light National Laboratory - Campinas, 02/28/2019                                                         |
|	Author: Allan S. B. Bugyi	(allan.bugyi@lnls.br)									      |
|	Version: 1.1														      |
|	Tested                                                                                                                        |
|                                                                                                                                     |
|       License:                                                                                                                      |
|        This software is distributed under the following ISC license:                                                                |
|                                                                                                                                     |
|        Copyright © 2018 BRAZILIAN SYNCHROTRON LIGHT SOURCE <sol@lnls.br>                                                            |
|                                                                                                                                     |
|        Permission to use, copy, modify, and/or distribute this software for any                                                     |
|        purpose with or without fee is hereby granted, provided that the above                                                       |
|        copyright notice and this permission notice appear in all copies.                                                            |
|                                                                                                                                     |
|        THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES                                                     |
|        WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF                                                             |
|        MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR                                                     |
|        ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES                                                       |
|        WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION                                                 |
|        OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN                                                       |
|        CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.                                                                     |
|_____________________________________________________________________________________________________________________________________|*/

#include<cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include<thread> 

//EPICS includes
#include <iocsh.h>
#include <epicsExport.h>
#include <registryFunction.h>
#include <subRecord.h>

//AsynPortDriver include
#include <asynPortDriver.h>

//SmarAct includes
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

using namespace std;
static const char *driverName = "PicoScaledriver";

#include "picoScaledrv.h"

//------------------------------------------ AsynPortDriver ------------------------------------------
PicoScaledrv::PicoScaledrv(const char *portName, const char *ip) 
	: asynPortDriver(portName, MAX_SIGNALS, /*NUM_PARAMS,*/
	asynInt32Mask | asynFloat64Mask | asynDrvUserMask,// Interfaces that we implement
	asynInt32Mask | asynFloat64Mask,// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
	0, 0) /* Default priority and stack size */
{
	createParam(pos_ch0_longInValueString, asynParamInt32, &pos_ch0_longInValue);
	createParam(vel_ch0_longInValueString, asynParamInt32, &vel_ch0_longInValue);
	createParam(acc_ch0_longInValueString, asynParamInt32, &acc_ch0_longInValue);
	createParam(swraw_ch0_analogInValueString, asynParamFloat64, &swraw_ch0_analogInValue);
	createParam(s2wraw_ch0_analogInValueString, asynParamFloat64, &s2wraw_ch0_analogInValue);
        createParam(sw_ch0_analogInValueString, asynParamFloat64, &sw_ch0_analogInValue);
        createParam(s2w_ch0_analogInValueString, asynParamFloat64, &s2w_ch0_analogInValue);
	createParam(swquality_ch0_analogInValueString, asynParamFloat64, &swquality_ch0_analogInValue);
	createParam(s2wquality_ch0_analogInValueString, asynParamFloat64, &s2wquality_ch0_analogInValue);
	//createParam(cntrZero_ch0_longInValueString, asynParamInt32, &cntrZero_ch0_longInValue);
	//createParam(cntrOne_ch0_longInValueString, asynParamInt32, &cntrOne_ch0_longInValue);
	createParam(envtemp_ch0_longInValueString, asynParamInt32, &envtemp_ch0_longInValue);
	createParam(envHum_ch0_longInValueString, asynParamInt32, &envHum_ch0_longInValue);
	createParam(envPress_ch0_longInValueString, asynParamInt32, &envPress_ch0_longInValue);
	/*createParam(gpioAdc0_ch0_longInValueString, asynParamInt32, &gpioAdc0_ch0_longInValue);
	createParam(gpioAdc1_ch0_longInValueString, asynParamInt32, &gpioAdc1_ch0_longInValue);
	createParam(gpioAdc2_ch0_longInValueString, asynParamInt32, &gpioAdc2_ch0_longInValue);
	createParam(calcSys0_ch0_longInValueString, asynParamInt32, &calcSys0_ch0_longInValue);
	createParam(calcSys1_ch0_longInValueString, asynParamInt32, &calcSys1_ch0_longInValue);
	createParam(calcSys2_ch0_longInValueString, asynParamInt32, &calcSys2_ch0_longInValue);
	createParam(calcSys3_ch0_longInValueString, asynParamInt32, &calcSys3_ch0_longInValue);
	createParam(calcSys4_ch0_longInValueString, asynParamInt32, &calcSys4_ch0_longInValue);
	createParam(calcSys5_ch0_longInValueString, asynParamInt32, &calcSys5_ch0_longInValue);
	createParam(calcSys6_ch0_longInValueString, asynParamInt32, &calcSys6_ch0_longInValue);
	createParam(calcSys7_ch0_longInValueString, asynParamInt32, &calcSys7_ch0_longInValue);*/
	createParam(pos_ch1_longInValueString, asynParamInt32, &pos_ch1_longInValue);
	createParam(vel_ch1_longInValueString, asynParamInt32, &vel_ch1_longInValue);
	createParam(acc_ch1_longInValueString, asynParamInt32, &acc_ch1_longInValue);
	createParam(swraw_ch1_analogInValueString, asynParamFloat64, &swraw_ch1_analogInValue);
	createParam(s2wraw_ch1_analogInValueString, asynParamFloat64, &s2wraw_ch1_analogInValue);
        createParam(sw_ch1_analogInValueString, asynParamFloat64, &sw_ch1_analogInValue);
        createParam(s2w_ch1_analogInValueString, asynParamFloat64, &s2w_ch1_analogInValue);        
	createParam(swquality_ch1_analogInValueString, asynParamFloat64, &swquality_ch1_analogInValue);
	createParam(s2wquality_ch1_analogInValueString, asynParamFloat64, &s2wquality_ch1_analogInValue);
	createParam(pos_ch2_longInValueString, asynParamInt32, &pos_ch2_longInValue);
	createParam(vel_ch2_longInValueString, asynParamInt32, &vel_ch2_longInValue);
	createParam(acc_ch2_longInValueString, asynParamInt32, &acc_ch2_longInValue);
	createParam(swraw_ch2_analogInValueString, asynParamFloat64, &swraw_ch2_analogInValue);
	createParam(s2wraw_ch2_analogInValueString, asynParamFloat64, &s2wraw_ch2_analogInValue);
        createParam(sw_ch2_analogInValueString, asynParamFloat64, &sw_ch2_analogInValue);
        createParam(s2w_ch2_analogInValueString, asynParamFloat64, &s2w_ch2_analogInValue);
	createParam(swquality_ch2_analogInValueString, asynParamFloat64, &swquality_ch2_analogInValue);
	createParam(s2wquality_ch2_analogInValueString, asynParamFloat64, &s2wquality_ch2_analogInValue);
	createParam(connectionStatus_binaryInValueString, asynParamInt32, &connectionStatus_binaryInValue); 
        createParam(streamStatus_binaryInValueString, asynParamInt32, &streamStatus_binaryInValue); 
	createParam(framerate_longOutValueString, asynParamInt32, &framerate_longOutValue);
	createParam(bufferaggr_mbboValueString, asynParamInt32, &bufferaggr_mbboValue);
	createParam(buffersnum_longOutValueString, asynParamInt32, &buffersnum_longOutValue);
	createParam(interleaving_binaryOutValueString, asynParamInt32, &interleaving_binaryOutValue);
	createParam(channelindx_mbboValueString, asynParamInt32, &channelindx_mbboValue);
	createParam(datasrcindx_mbboValueString, asynParamInt32, &datasrcindx_mbboValue);
	createParam(streamstart_mbboValueString, asynParamInt32, &streamstart_mbboValue);
        createParam(poll_binaryOutValueString, asynParamInt32, &poll_binaryOutValue);
        
	picoScale_open(ip);
        PicoScaleInitializingRoutinesRun();
}

// --- AsynPortDriver extended methods ---
asynStatus PicoScaledrv::writeInt32(asynUser *pasynUser, epicsInt32 value){
	    int function = pasynUser->reason;
	    int addr=0;
	    asynStatus status = asynSuccess;
	    const char* functionName = "writeInt32";

	    status = getAddress(pasynUser, &addr); if (status != asynSuccess) return(status);
            
            if(function==bufferaggr_mbboValue && firstExe==false){
                getIntegerParam(interleaving_binaryOutValue, &streamConfig.interleavingEnabled);
                if(streamConfig.interleavingEnabled==1 && value!=0){
                    cout<<"Error: while interleaving is active buffer aggregation should be 0.\n";
                    return asynError;
                }
            }
                
	    /* Set the parameter in the parameter library. */
	    status = (asynStatus) setIntegerParam(addr, function, value);
		
            if(function==framerate_longOutValue){
                picoScale_setFramerate();
            }else if(function==streamstart_mbboValue && streamingActive==false){
                if(value==0){
                    streamingActive = true;
                    setIntegerParam(streamStatus_binaryInValue, 1);
                    callParamCallbacks();
                    picoScale_stream();
                    setIntegerParam(streamStatus_binaryInValue, 0);
                    callParamCallbacks();                    
                }else if(value==1){
                    streamingActive = true;
                    setIntegerParam(streamStatus_binaryInValue, 1);
                    callParamCallbacks();
                    picoScale_streamPVA_allChannels();
                    setIntegerParam(streamStatus_binaryInValue, 0);
                    callParamCallbacks();                    
                }else if(value==2){
                    streamingActive = true;
                    setIntegerParam(streamStatus_binaryInValue, 1);
                    callParamCallbacks();
                    picoScale_streamPosition_allChannels();
                    setIntegerParam(streamStatus_binaryInValue, 0);
                    callParamCallbacks();
                }
            }else if(function==poll_binaryOutValue){
                if(value==1){
                    picoScale_poll();
                    setIntegerParam(poll_binaryOutValue, 0);
                    callParamCallbacks();
                }
            }
                
	    /* Do callbacks so higher layers see any changes */
	    status = (asynStatus) callParamCallbacks(addr, addr);

	    if (status) 
		epicsSnprintf(pasynUser->errorMessage, pasynUser->errorMessageSize, 
		          "%s:%s: status=%d, function=%d, value=%d", 
		          driverName, functionName, status, function, value);
	    else        
		asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, 
		      "%s:%s: function=%d, value=%d\n", 
		      driverName, functionName, function, value);
	    return status;
}

// ----------------------------

/*  PicoScale to EPICS data types conversion
     *  Channel 0 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     *      Datasource      Desc.       Data type   EPICS casting to
     *          0           Position    int64_t     long (int)
     *          1           Velocity    int64_t     long (int)
     *          2           Accelerat   int64_t     long (int)
     *          3           SwRaw       double      analog (double)
     *          4           S2wRaw      double      analog (double)
     *          5           Sw          double      analog (double)
     *          6           S2w         double      analog (double)
     *          7           SwQuality   double      analog (double)
     *          8           S2wQuality  double      analog (double)
     *          11          Env Temp    int64_t     long (int)
     *          12          Env Hum     int64_t     long (int)
     *          13          Env Pres    int64_t     long (int)
     *  Channel 1 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     *      Datasource      Desc.       Data type   EPICS casting to
     *          0           Position    int64_t     long (int)
     *          1           Velocity    int64_t     long (int)
     *          2           Accelerat   int64_t     long (int)
     *          3           SwRaw       double      analog (double)
     *          4           S2wRaw      double      analog (double)
     *          5           Sw          double      analog (double)
     *          6           S2w         double      analog (double)
     *          7           SwQuality   double      analog (double)
     *          8           S2wQuality  double      analog (double)
     *  Channel 2 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     *      Datasource      Desc.       Data type   EPICS casting to
     *          0           Position    int64_t     long (int)
     *          1           Velocity    int64_t     long (int)
     *          2           Accelerat   int64_t     long (int)
     *          3           SwRaw       double      analog (double)
     *          4           S2wRaw      double      analog (double)
     *          5           Sw          double      analog (double)
     *          6           S2w         double      analog (double)
     *          7           SwQuality   double      analog (double)
     *          8           S2wQuality  double      analog (double)     
*/

//Initializing routine for stream modes:
// - PVA (Position/Velocity/Acceleration datasources) All channels;
// - Position data sources All channels.
void PicoScaledrv::PicoScaleInitializingRoutinesRun(){
        dataSource.address.channelIndex = 0;
	dataSource.address.dataSourceIndex = 0;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 0),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
	enabled_Positiondtsrcs_stream.push_back(dataSource);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 0;
	dataSource.address.dataSourceIndex = 1;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 1),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);
	
	dataSource.address.channelIndex = 0;
	dataSource.address.dataSourceIndex = 2;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 2),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);
	
	dataSource.address.channelIndex = 1;
	dataSource.address.dataSourceIndex = 0;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 0),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_Positiondtsrcs_stream.push_back(dataSource);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 1;
	dataSource.address.dataSourceIndex = 1;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 1),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 1;
	dataSource.address.dataSourceIndex = 2;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 2),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 2;
	dataSource.address.dataSourceIndex = 0;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 0),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_Positiondtsrcs_stream.push_back(dataSource);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 2;
	dataSource.address.dataSourceIndex = 1;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 1),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	dataSource.address.channelIndex = 2;
	dataSource.address.dataSourceIndex = 2;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 2),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
        enabled_PVAdtsrcs_stream.push_back(dataSource);

	for(unsigned int i=0; i<enabled_PVAdtsrcs_stream.size(); i++){
		PVA_frame_size += enabled_PVAdtsrcs_stream[i].dataSize;	
	}
	
	for(unsigned int i=0; i<enabled_Positiondtsrcs_stream.size(); i++){
		PositionAllChannels_frame_size += enabled_Positiondtsrcs_stream[i].dataSize;	
	}

	return;
}

int32_t PicoScaledrv::getDataSize(int32_t dataType)
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

unsigned int PicoScaledrv::configureStream(SA_SI_Handle handle){
    getIntegerParam(interleaving_binaryOutValue, &streamConfig.interleavingEnabled);
    getIntegerParam(bufferaggr_mbboValue, &streamConfig.streamBufferAggregation);
    getIntegerParam(buffersnum_longOutValue, &streamConfig.numberOfStreamBuffers);
    
    // configure frame aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_AGGREGATION_PROP,0,0),streamConfig.frameAggregation);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    // configure frame rate
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0),streamConfig.frameRate);
    if (result != SA_SI_OK){
	 //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    // configure stream buffer aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFER_AGGREGATION_PROP,0,0),streamConfig.streamBufferAggregation);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    // configure interleaving
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFERS_INTERLEAVED_PROP,0,0),streamConfig.interleavingEnabled);
    if (result != SA_SI_OK){
	//error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    // configure number of stream buffers
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_NUMBER_OF_STREAMBUFFERS_PROP,0,0),streamConfig.numberOfStreamBuffers);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    return SA_SI_OK;
}

//Registering the data source(s) streamed values on records
void PicoScaledrv::picoScale_dataSourcesValues_EPICSRecordsWriting(void *pValue, size_t dataSourceIndex){
    int aux_int64_t_prop;
    float aux_float64_t_prop;
    VariantValue v;
    
    switch(streamConfig.enabledDataSources[dataSourceIndex].address.channelIndex){
        case 0:
            switch(streamConfig.enabledDataSources[dataSourceIndex].address.dataSourceIndex){
                case 0:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i48value);
                    setIntegerParam(pos_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                 
                break;
                case 3:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                /*case 9:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setIntegerParam(); 
                    callParamCallbacks(); 
                break;
                case 10:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setIntegerParam(); 
                    callParamCallbacks(); 
                break;*/
                case 11:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envtemp_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 12:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envHum_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                            
                break;
                case 13:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envPress_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                            
                break;                
            }
        break;
        case 1:
            switch(streamConfig.enabledDataSources[dataSourceIndex].address.dataSourceIndex){
                case 0:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i48value);
                    setIntegerParam(pos_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 3:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;                
            }
        break;
        case 2:
            switch(streamConfig.enabledDataSources[dataSourceIndex].address.dataSourceIndex){
                case 0:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i48value);
                    setIntegerParam(pos_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    v.i64value = *(const int64_t*)(pValue);
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 3:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    v.f64value = *(const double*)(pValue);
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;                
            }
        break;
    }
}

void PicoScaledrv::processBuffer(const SA_SI_DataBuffer *buffer){
    // Each buffer holds as many frames as we have defined by the stream
    // buffer aggregation.
    // The structure of the buffer depends on whether we use interleaving
    // or not and which data sources were enabled for streaming. In this
    // case we've enabled a position data source and a GPIO ADC.
    if (streamConfig.interleavingEnabled){
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
        for (unsigned int frame = 0; frame<buffer->info.numberOfFrames; frame++){
            int32_t offset = 0;
            for (size_t dataSourceIterator=0; dataSourceIterator < buffer->info.numberOfSources; dataSourceIterator++){
                void *dataSourceValue = &buffer->data[0][frame*streamConfig.frameSize + offset];
                offset += streamConfig.enabledDataSources[dataSourceIterator].dataSize;
		picoScale_dataSourcesValues_EPICSRecordsWriting(dataSourceValue, dataSourceIterator);
            }
        }
    }
    else{ // non-interleaving - Not used so far/*
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
        /*for (size_t dataSourceIterator = 0; dataSourceIterator < buffer->info.numberOfSources; dataSourceIterator++)
        {
            for (unsigned int frame = 0; frame < buffer->info.numberOfFrames; frame++)
	    {
                void *dataSourceValue = &buffer->data[dataSourceIterator][frame*datasrcs_dataSizes[dataSourceIterator]];
            }
        }*/
    }
    // Note: The following code line is an example how it should *not* be
    // implemented. Printing to standard out is a relatively time consuming
    // operation and should be avoided at this place. At low data rates it
    // might work, but especially at high data rates the PicoScale generates
    // data faster than the host can process them, very likely leading to
    // a buffer overflow error!
    //cout << "Received " << buffer->info.numberOfFrames << " frames." << endl;
}

unsigned int PicoScaledrv::receiveStreamBuffer(SA_SI_Handle handle, unsigned int timeout, bool &lastFrame){
    SA_SI_Event ev;
    unsigned int result = SA_SI_WaitForEvent(handle,&ev,timeout);
    if(result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return result;
    }
    if(ev.type == SA_SI_STREAMBUFFER_READY_EVENT){
        // get buffer data
	const SA_SI_DataBuffer *pBuffer;
        result = SA_SI_AcquireBuffer(handle,ev.bufferId,&pBuffer);
        if(result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return result;
	}
        processBuffer(pBuffer);
        if(pBuffer->info.flags & SA_SI_STREAM_END_FLAG){
            lastFrame = true;
	}
        result = SA_SI_ReleaseBuffer(handle,ev.bufferId);
        if(result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return result;
	}
    }
    else{
        cout << "Received unexpected event type: " << ev.type << " (parameter: " << ev.devEventParameter << ")" << endl;
        return SA_SI_OTHER_ERROR;
    }
    return SA_SI_OK;
}

void PicoScaledrv::picoScale_open(const char *ip){	
    if((ip!=NULL) && (ip[0]!='\0')){
	const char *locator_part1 = "network:";
	const char *locator_part2 = ":55555";
        char *locator	= (char*) calloc(strlen(locator_part1) + strlen(ip) + strlen(locator_part2) +1, sizeof(char));
	strcpy(locator, locator_part1);
	strcat(locator, ip);
	strcat(locator, locator_part2);

	result = (SA_SI_Open(&handle, locator,""));
	
	if(result != SA_SI_OK){
                //error
		cout<<"Could not connect to device. Error: "<<result<<" -- Check ERROR PV.\n";
                setIntegerParam(connectionStatus_binaryInValue, 0);
                callParamCallbacks();
		return;
    	}
        setIntegerParam(connectionStatus_binaryInValue, 1);
        callParamCallbacks();
        
        result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_SYS_FULL_ACCESS_CONNECTION_PROP,0,0), SA_SI_ENABLED);
        
        if(result != SA_SI_OK){
            //error
            cout<<"Could not set Full Access Connection. Error: "<<result<<" -- Check ERROR PV.\n";
    	}
        
        //Activating Dead Path Correction for all the 3 channels, so the measurements account for the environmental module input
        result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_CH_DEAD_PATH_CORRECTION_ENABLED_PROP,0,0), SA_SI_ENABLED);
        
        if(result != SA_SI_OK){
            //error
            cout<<"Dead path correction for channel 0 not activated. Error: "<<result<<" -- Check ERROR PV.\n";
        }
        
        result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_CH_DEAD_PATH_CORRECTION_ENABLED_PROP,1,0), SA_SI_ENABLED);
        
        if(result != SA_SI_OK){
            //error
            cout<<"Dead path correction for channel 1 not activated. Error: "<<result<<" -- Check ERROR PV.\n";
        }
        
        result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_CH_DEAD_PATH_CORRECTION_ENABLED_PROP,2,0), SA_SI_ENABLED);
        
        if(result != SA_SI_OK){
            //error
            cout<<"Dead path correction for channel 2 not activated. Error: "<<result<<" -- Check ERROR PV.\n";
        }
    }else{
        //error
        cout<<"Error: Invalid IP!"<<"\n";
        setIntegerParam(connectionStatus_binaryInValue, 0);
        callParamCallbacks();
        return;
    }
    return;
}

void PicoScaledrv::picoScale_setFramerate(){
	if(firstExe==false) getIntegerParam(framerate_longOutValue, &streamConfig.frameRate);
	else{
		streamConfig.frameRate=1;
		firstExe=false;
	}

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0), streamConfig.frameRate);
	
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
    	}
	
	double preciseFrameRate;
	result = SA_SI_GetProperty_f64(handle, SA_SI_EPK(SA_SI_PRECISE_FRAME_RATE_PROP,0,0),&preciseFrameRate,0); //the real operational framerate set by picoScale
    	
	if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
    	}

	streamConfig.frameRate = (int32_t) preciseFrameRate;
	setIntegerParam(framerate_longOutValue, (int) preciseFrameRate);
	callParamCallbacks();
        
	//frame aggregation based on framerate value accordingly to PicoScale's Programming guide
	switch(streamConfig.frameRate){
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
		case 1220:
			streamConfig.frameAggregation = (int32_t) 32;
		break;
		case 2440:
			streamConfig.frameAggregation = (int32_t) 64;
		break;
		case 4880:
			streamConfig.frameAggregation = (int32_t) 128;
		break;
		case 9770:
			streamConfig.frameAggregation = (int32_t) 256;
		break;
		case 19530:
			streamConfig.frameAggregation = (int32_t) 512;
		break;
		case 625000:
		case 312500:
		case 156250:
		case 78130:
		case 39060:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
		case 10000000:
		case 5000000:
		case 2500000:
		case 1250000:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
	}
	return;
}

//method for streaming a single user defined data source
void PicoScaledrv::picoScale_stream(){ 
    lastFrame = false;
    int channelIndex, datasrcIndex, interleavingMode, bufferAggr, buffersNum;

    enabled_singledtsrc_stream.clear();

    getIntegerParam(channelindx_mbboValue, &channelIndex);
    getIntegerParam(datasrcindx_mbboValue, &datasrcIndex);
    dataSource.address.channelIndex = channelIndex;
    dataSource.address.dataSourceIndex = datasrcIndex;

    result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, dataSource.address.channelIndex, dataSource.address.dataSourceIndex),&dataSource.dataType,0); 
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    dataSource.dataSize = getDataSize(dataSource.dataType);
    streamConfig.frameSize = dataSource.dataSize;
    enabled_singledtsrc_stream.push_back(dataSource);

    getIntegerParam(interleaving_binaryOutValue, &interleavingMode);
    getIntegerParam(bufferaggr_mbboValue, &bufferAggr);
    getIntegerParam(buffersnum_longOutValue, &buffersNum);
    
    streamConfig.interleavingEnabled = interleavingMode;
    streamConfig.streamBufferAggregation = bufferAggr;
    streamConfig.numberOfStreamBuffers = buffersNum;

    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,dataSource.address.channelIndex, dataSource.address.dataSourceIndex),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = configureStream(handle);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    //stream begins!
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }	

    streamConfig.enabledDataSources = enabled_singledtsrc_stream;

    while(!lastFrame){
	result = receiveStreamBuffer(handle, 2000, lastFrame);
	if (result != SA_SI_OK){
	        //error
	        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
	        return;
	}
    }
    return;
}

//method for streaming position/velocity/acceleration measurements from all channels
void PicoScaledrv::picoScale_streamPVA_allChannels(){
    lastFrame = false;
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,1),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,2),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,1),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,2),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,1),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,2),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }

    result = configureStream(handle);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    //stream begins!
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }	

    streamConfig.enabledDataSources = enabled_PVAdtsrcs_stream;
    streamConfig.frameSize = PVA_frame_size;
    
    while (!lastFrame){
        result = receiveStreamBuffer(handle, 2000, lastFrame);
        if (result != SA_SI_OK){
            //error
            cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
            return;
        }
    }
    return;
}

//method for streaming position measurements from all (3) channels
void PicoScaledrv::picoScale_streamPosition_allChannels(){	
    lastFrame = false;
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }

    result = configureStream(handle);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }
    //stream begins!
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
    if (result != SA_SI_OK){
        //error
        cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
        return;
    }	

    streamConfig.enabledDataSources = enabled_Positiondtsrcs_stream;
    streamConfig.frameSize = PositionAllChannels_frame_size;

    while (!lastFrame){
            result = receiveStreamBuffer(handle, 2000, lastFrame);
            if (result != SA_SI_OK){
                //error
                cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
                return;
            }
    }
    return;	
}

void PicoScaledrv::picoScale_poll(){
    int channelIndex, datasrcIndex, aux_int64_t_prop;
    float aux_float64_t_prop;
    int32_t dataType;
    VariantValue v;
    getIntegerParam(channelindx_mbboValue, &channelIndex);
    getIntegerParam(datasrcindx_mbboValue, &datasrcIndex);
    
    result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, channelIndex, datasrcIndex),&dataType,0); 
    
    if (result != SA_SI_OK){
                //error
                cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
                return;
    }
    
    switch(dataType){
        case SA_SI_INT32_DTYPE:
        case SA_SI_UINT32_DTYPE:
        case SA_SI_INT48_DTYPE:
        case SA_SI_UINT48_DTYPE:
        case SA_SI_INT64_DTYPE:
        case SA_SI_UINT64_DTYPE:
                result = SA_SI_GetValue_i64(handle,channelIndex,datasrcIndex,&v.i64value);
                if (result != SA_SI_OK){
                    //error
                    cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
                    return;
                }
            break;
        case SA_SI_FLOAT32_DTYPE:
        case SA_SI_FLOAT64_DTYPE:
                result = SA_SI_GetValue_f64(handle,channelIndex,datasrcIndex,&v.f64value);
                if (result != SA_SI_OK){
                    //error
                    cout<<"Error: "<<result<<" -- Check ERROR PV.\n";
                    return;
                }
        break;
    }
    
    switch(channelIndex){
        case 0:
            switch(datasrcIndex){
                case 0:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(pos_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                 
                break;
                case 3:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch0_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                /*case 9:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setIntegerParam(); 
                    callParamCallbacks(); 
                break;
                case 10:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setIntegerParam(); 
                    callParamCallbacks(); 
                break;*/
                case 11:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envtemp_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 12:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envHum_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                            
                break;
                case 13:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(envPress_ch0_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                            
                break;
            }
        break;
        case 1:
            switch(datasrcIndex){
                case 0:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(pos_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch1_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 3:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch1_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
            }
        break;
        case 2:
            switch(datasrcIndex){
                case 0:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(pos_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();
                break;
                case 1:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(vel_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 2:
                    aux_int64_t_prop = static_cast<int>(v.i64value);
                    setIntegerParam(acc_ch2_longInValue, aux_int64_t_prop); 
                    callParamCallbacks();                    
                break;
                case 3:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swraw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 4:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wraw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 5:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(sw_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 6:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2w_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 7:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(swquality_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
                case 8:
                    aux_float64_t_prop = static_cast<float>(v.f64value);
                    setDoubleParam(s2wquality_ch2_analogInValue, aux_float64_t_prop); 
                    callParamCallbacks(); 
                break;
            }
        break;
    }
    
    return;
}
//---------------------------------------------------------------------------------------------------------

//------------------------------------------ IOC Shell Functions ------------------------------------------
//--- Create driver function
extern "C" int PicoScaleCreateDriver(const char *portName, const char *ip){
	PicoScaledrv *picoScaledrv = new PicoScaledrv(portName, ip);
	picoScaledrv = NULL;
	return(asynSuccess);
}

static const iocshArg portNameArg = { "Port name", iocshArgString};
static const iocshArg ipArg = { "IP", iocshArgString};
static const iocshArg * const createDriverArgs[] = {&portNameArg, &ipArg};
static const iocshFuncDef createDriverFuncDef = {"PicoScaleCreateDriver", 2, createDriverArgs};

static void createDriverCallFunc(const iocshArgBuf *args){
	PicoScaleCreateDriver(args[0].sval, args[1].sval);
}

void drvPicoScaleRegister(void){
	iocshRegister(&createDriverFuncDef,createDriverCallFunc);
}

extern "C" {
	epicsExportRegistrar(drvPicoScaleRegister);
}
//----------------------------------------------------------------------------------------------------------

