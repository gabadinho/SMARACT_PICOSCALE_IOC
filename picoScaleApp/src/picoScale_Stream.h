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
