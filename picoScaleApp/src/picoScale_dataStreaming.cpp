#include <iostream>
#include <vector>
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

using namespace std;

string locator("network:10.0.9.108:55555");
/*
struct DataSourceDescription_t {
    int32_t componentID;
    int32_t componentIndex;
    int32_t dataSourceType;
};

struct DataSourceAddress_t {
    uint8_t channelIndex;
    uint8_t dataSourceIndex;
};

struct DataSource_t {
    DataSourceAddress_t address;
    int32_t dataType;
    int32_t dataSize;
};

struct StreamConfig_t {
    vector<DataSource_t> enabledDataSources;
    int32_t frameSize;
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

struct DataSourceData_t {
    vector<VariantValue> data;
};

struct StreamData_t {
    vector<DataSourceData_t> dataSource;
};

StreamConfig_t streamConfig;                // stores the stream configuration
//StreamData_t streamData;                    // stores the stream data received from the device
/*
void writesFile_positionxtime()
{
	FILE *fp;
	fp = fopen("picoScale_positionMeasr.txt", "a");
	// iterate over all frames
	for (size_t frame = 0; frame < streamData.dataSource[0].data.size(); frame++)
	{
		//cout << "frame " << frame << ": ";
		// iterate over all data sources of the frame
		for (size_t dataSource = 0; dataSource < streamData.dataSource.size(); dataSource++)
		{
            		switch (streamConfig.enabledDataSources[dataSource].dataType)
            		{
				case SA_SI_INT8_DTYPE:
				    fputc(((int32_t)streamData.dataSource[dataSource].data[frame].i8value), fp);
				    break;
				case SA_SI_UINT8_DTYPE:
				    fputc(((uint32_t)streamData.dataSource[dataSource].data[frame].u8value), fp);
				    break;
				case SA_SI_INT16_DTYPE:
				    fputc(((int32_t)streamData.dataSource[dataSource].data[frame].i16value), fp);
				    break;
				case SA_SI_UINT16_DTYPE:
				    fputc(((uint32_t)streamData.dataSource[dataSource].data[frame].u16value), fp);
				    break;
				case SA_SI_INT32_DTYPE:
				    fputc((streamData.dataSource[dataSource].data[frame].i32value), fp);
				    break;
				case SA_SI_UINT32_DTYPE:
				    fputc((streamData.dataSource[dataSource].data[frame].u32value), fp);
				    break;
				case SA_SI_INT48_DTYPE:
				    fputc(((int64_t)streamData.dataSource[dataSource].data[frame].i64value), fp);
				    break;
				case SA_SI_UINT48_DTYPE:
				    fputc(((uint64_t)streamData.dataSource[dataSource].data[frame].u64value), fp);
				    break;
				case SA_SI_INT64_DTYPE:
				    fputc(((int64_t) streamData.dataSource[dataSource].data[frame].i64value), fp);
				    break;
				case SA_SI_UINT64_DTYPE:
				    fputc(((uint64_t) streamData.dataSource[dataSource].data[frame].u64value), fp);
				    break;
				case SA_SI_FLOAT32_DTYPE:
				    fputc((streamData.dataSource[dataSource].data[frame].f32value), fp);
				    break;
				case SA_SI_FLOAT64_DTYPE:
				    fputc((streamData.dataSource[dataSource].data[frame].f64value), fp);
				    break;
			    }
        	}
    	}
	fclose(fp);
}

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

void appendValue(unsigned int dataSource, void *pValue, FILE *fp)
{
    VariantValue v;
    switch (streamConfig.enabledDataSources[dataSource].dataType)
    {
        case SA_SI_INT8_DTYPE:
            v.i8value = *(const int8_t*)(pValue);
	    //cout << "1";
            break;
        case SA_SI_UINT8_DTYPE:
            v.u8value = *(const uint8_t*)(pValue);
	    //cout << "2";
            break;
        case SA_SI_INT16_DTYPE:
            v.i16value = *(const int16_t*)(pValue);
	    //cout << "3";
            break;
        case SA_SI_UINT16_DTYPE:
            v.u16value = *(const uint16_t*)(pValue);
	    //cout << "4";
            break;
        case SA_SI_INT32_DTYPE:
            v.i32value = *(const int32_t*)(pValue);
	    //cout << "5";
            break;
        case SA_SI_UINT32_DTYPE:
            v.u32value = *(const uint32_t*)(pValue);
	    //cout << "6";
            break;
        case SA_SI_INT48_DTYPE:
            v.i48value = *(const int64_t*)(pValue);
	    fprintf(fp, "%li\n", v.i48value);
	    cout << (const int64_t*)v.i48value;
	    //cout << "7";
            break;
        case SA_SI_UINT48_DTYPE:
            v.u48value = *(const uint64_t*)(pValue);
	    //cout << "8";
            break;
        case SA_SI_INT64_DTYPE:
            v.i64value = *(const int64_t*)(pValue);
	    //cout << "9";
            break;
        case SA_SI_UINT64_DTYPE:
            v.u64value = *(const uint64_t*)(pValue);
	    //cout << "10";
            break;
        case SA_SI_FLOAT32_DTYPE:
            v.f32value = *(const float*)(pValue);
	    //cout << "11";
            break;
        case SA_SI_FLOAT64_DTYPE:
	    //cout << "12";
            v.f64value = *(const double*)(pValue);
            break;
        default:
            // shouldn't happen
            v.i32value = 0;
            break;
    }
    //streamData.dataSource[dataSource].data.push_back(v);
}

void processBuffer(const SA_SI_DataBuffer *buffer)
{
    FILE *fp;
    fp = fopen("picoScale_positionMeasr.txt", "a");
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
                void *dataSourceValue = &buffer->data[0][frame*streamConfig.frameSize + offset];
               // appendValue(dataSource,dataSourceValue);
                offset += streamConfig.enabledDataSources[dataSource].dataSize;
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
		//var = (*(int*) buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize]);
		//cout << var + "\n";
		//cout<< ((long int)buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize]) + "\n";
		//fprintf(fp, "%li\n", var);
		//fputc(((int) buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize]), fp);
                void *dataSourceValue = &buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize];
                appendValue(dataSource,dataSourceValue, fp);
            }
        }
	fclose(fp);
    }
    // Note: The following code line is an example how it should *not* be
    // implemented. Printing to standard out is a relatively time consuming
    // operation and should be avoided at this place. At low data rates it
    // might work, but especially at high data rates the PicoScale generates
    // data faster than the host can process them, very likely leading to
    // a buffer overflow error!
    //cout << "Received " << buffer->info.numberOfFrames << " frames." << endl;
}

unsigned int receiveStreamBuffer(SA_SI_Handle handle, unsigned int timeout, bool &lastFrame)
{
    SA_SI_Event ev;
    unsigned int result = SA_SI_WaitForEvent(handle,&ev,timeout);
    if (result != SA_SI_OK)
        return result;
    if (ev.type == SA_SI_STREAMBUFFER_READY_EVENT)
    {
        // get buffer data
        const SA_SI_DataBuffer *pBuffer;
        result = SA_SI_AcquireBuffer(handle,ev.bufferId,&pBuffer);
        if (result != SA_SI_OK)
            return result;
        processBuffer(pBuffer);
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

unsigned int configureStream(SA_SI_Handle handle)
{
    unsigned int result;
    // prepare stream data container for received data
    //streamData.dataSource.resize(streamConfig.enabledDataSources.size());
    // configure frame aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_AGGREGATION_PROP,0,0),streamConfig.frameAggregation);
    if (result != SA_SI_OK){
	cout << "cond 1";
        return result;
    }
    // configure frame rate
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0),streamConfig.frameRate);
    if (result != SA_SI_OK){
         cout << "cond 2";
	 return result;
    }
    // read back actual frame rate
    cout << "Frame rate is ";
    double value;
    result = SA_SI_GetProperty_f64(handle, SA_SI_EPK(SA_SI_PRECISE_FRAME_RATE_PROP,0,0),&value,0);
    if (result != SA_SI_OK){
	cout << "cond 3";
        return result;
    }
    cout << value << "Hz" << endl;
    // configure stream buffer aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFER_AGGREGATION_PROP,0,0),streamConfig.streamBufferAggregation);
    if (result != SA_SI_OK){
	cout << result;
	cout << "cond 4";
        return result;
    }
    // configure interleaving
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFERS_INTERLEAVED_PROP,0,0),streamConfig.interleavingEnabled);
    if (result != SA_SI_OK){
           cout << "cond 5";
	   return result;
    }
    // configure number of stream buffers
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_NUMBER_OF_STREAMBUFFERS_PROP,0,0),streamConfig.numberOfStreamBuffers);
    if (result != SA_SI_OK){
	cout << "cond 6";
        return result;
    }
    return SA_SI_OK;
}



int main(int argc, char* argv[]){
	unsigned int result;
    	SA_SI_Handle handle;
    	result = SA_SI_Open(&handle,locator.c_str(),"");
	
	if (result != SA_SI_OK)
    	{
        	cout << "Could not connect to device. Error " << result << endl;
        	return result;
    	}

	//vector<DataSourceDescription_t> dataSourcesToEnable;
	//dataSourcesToEnable.push_back({SA_PS_CHANNEL_CID,0,SA_SI_POSITION_DSOURCE});
	
	DataSource_t dataSource;
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP,0,0),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
		return result;
	}
	dataSource.dataSize = getDataSize(dataSource.dataType);
	dataSource.address.channelIndex = 0;
	dataSource.address.dataSourceIndex = 0; 

	streamConfig.enabledDataSources.push_back(dataSource);
	streamConfig.interleavingEnabled = false;
    	streamConfig.frameAggregation = 1;
    	streamConfig.streamBufferAggregation = 0;   // "same as frame aggregation"
    	streamConfig.frameRate = 1;
    	streamConfig.numberOfStreamBuffers = 64;
	streamConfig.enabledDataSources.push_back(dataSource);
        streamConfig.frameSize += dataSource.dataSize;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		cout << "if 1";
        	return result;
	}
	result = configureStream(handle);
    	if (result != SA_SI_OK){
		cout << "if 2";
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
		cout << "if 3";
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
		cout << "if 4";
        	return result;
	}*/
	bool lastFrame = false;
	receiveStreamBuffer(handle,20000,lastFrame);
	/*
	for (int i=0;i<streamConfig.numberOfStreamBuffers;i++)
    	{
        	result = receiveStreamBuffer(handle,20000,lastFrame); // (lastFrame is ignored here)
        	if (result != SA_SI_OK)
            		return result;
    	}*/

	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle,2000,lastFrame);
		if (result != SA_SI_OK)
		    return result;
    	}
	//writesFile_positionxtime();
	return SA_SI_OK;
}

