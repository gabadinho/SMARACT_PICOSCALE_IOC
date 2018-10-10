/**********************************************************************
* SmarAct Sensor Interface API
* Copyright (c) 2016-2018 SmarAct GmbH
*
* File name: SmarActSI.h
* Author: Oliver Frick
*
* THIS  SOFTWARE, DOCUMENTS, FILES AND INFORMATION ARE PROVIDED 'AS IS'
* WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
* BUT  NOT  LIMITED  TO,  THE  IMPLIED  WARRANTIES  OF MERCHANTABILITY,
* FITNESS FOR A PURPOSE, OR THE WARRANTY OF NON-INFRINGEMENT.
* THE  ENTIRE  RISK  ARISING OUT OF USE OR PERFORMANCE OF THIS SOFTWARE
* REMAINS WITH YOU.
* IN  NO  EVENT  SHALL  THE  SMARACT  GMBH  BE  LIABLE  FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, CONSEQUENTIAL OR OTHER DAMAGES ARISING
* OUT OF THE USE OR INABILITY TO USE THIS SOFTWARE.
**********************************************************************/

#ifndef SMARACT_SI_H
#define SMARACT_SI_H

#include <stdlib.h>
#include <stdint.h>
#include <SmarActSIConstants.h>


#define SA_SI_VERSION_MAJOR                2
#define SA_SI_VERSION_MINOR                0
#define SA_SI_VERSION_UPDATE               8




#if defined(_WIN32)
#  define SA_SI_PLATFORM_WINDOWS
#elif defined(__linux__)
#  define SA_SI_PLATFORM_LINUX
#else
#  error "unsupported platform"
#endif


#if defined(SA_SI_PLATFORM_WINDOWS)
#  if !defined(_SA_SI_DIRECTLINK)
#    ifdef SA_SI_EXPORTS
#      define SA_SI_API __declspec(dllexport)
#    else
#      define SA_SI_API __declspec(dllimport)
#    endif
#  else
#    define SA_SI_API
#  endif
#  define SA_SI_CC __cdecl
#else
#  define SA_SI_API __attribute__ ((visibility ("default")))
#  define SA_SI_CC
#endif




#ifdef __cplusplus
extern "C" {
#endif


/*******************/
/* API ERROR CODES */
/*******************/

#define SA_SI_DEVICE_LIMIT_ERROR                        0xf000
#define SA_SI_INVALID_LOCATOR_ERROR                     0xf001
#define SA_SI_INITIALIZATION_ERROR                      0xf002
#define SA_SI_NOT_INITIALIZED_ERROR                     0xf003
#define SA_SI_COMMUNICATION_ERROR                       0xf004
#define SA_SI_QUERYBUFFER_SIZE_ERROR                    0xf006
#define SA_SI_INVALID_HANDLE_ERROR                      0xf007
#define SA_SI_DATA_SOURCE_ENABLED_ERROR                 0xf008
#define SA_SI_INVALID_STREAMBUFFER_ID_ERROR             0xf009
#define SA_SI_STREAM_SEQUENCE_ERROR                     0xf00a
#define SA_SI_NO_DATABUFFER_AVAILABLE_ERROR             0xf00b
#define SA_SI_STREAMBUFFER_NOT_ACQUIRED_ERROR           0xf00d
#define SA_SI_UNEXPECTED_PACKET_RECEIVED_ERROR          0xf00f
#define SA_SI_CANCELED_ERROR                            0xf010
#define SA_SI_BUFFER_INTERLEAVING_ERROR                 0xf012
#define SA_SI_DRIVER_ERROR                              0xf013
#define SA_SI_DATA_OBJECT_BUSY_ERROR                    0xf014


/**************/
/* API EVENTS */
/**************/

/* event returned by SA_SI_WaitForEvent when a new stream buffer is
   ready. this event type does not have to be enabled via property
   SA_SI_EVENT_NOTIFICATION_ENABLED_PROP, it is automatically
   sent if streaming is enabled. */
#define SA_SI_STREAMBUFFER_READY_EVENT                  0xf000

/* sent immediately after the stream has stopped */
#define SA_SI_STREAM_STOPPED_EVENT                      0xf001

/******************/
/* API PROPERTIES */
/******************/

/* specifies the data type of the received and decompressed frame
   values in the streambuffers. this data type can be the same as
   the data source's data type if that type has 8,15,32,64 bits, or
   it can be set to a larger data type.
   (R/W), index1: channel, index2: data source, value: data type of
   streambuffer value. default: same as data source data type or
   next bigger machine data type: i/u8,16,32,64 or F32,F64 */
#define SA_SI_STREAMBUFFER_DATA_TYPE_PROP               0xf000

/* the number of buffers used to store incoming stream data (>= 2).
   (R/W), index1: -, index2: -, value: [2...256], default=2 */
#define SA_SI_NUMBER_OF_STREAMBUFFERS_PROP              0xf001

/* if enabled, the received frames are stored consecutively in one
   memory block of a streambuffer. if disabled, the frames are
   split and the values of each data source are stored in different
   memory blocks.
   (R/W), index1: -, index2: -, value: ENABLED/DISABLED, default=ENABLED */
#define SA_SI_STREAMBUFFERS_INTERLEAVED_PROP            0xf002

/* number of frames that are aggregated in a streambuffer.
   if set to 0, the streambuffer aggregation will be the same
   as the SI device's streaming packet aggregation. if it is not
   0, it should be larger than the SI streaming packet aggr.
   (R/W), index1: -, index2: -, value: 0 or >=32, default=0 */
#define SA_SI_STREAMBUFFER_AGGREGATION_PROP             0xf003


/*******************/
/* OTHER CONSTANTS */
/*******************/

#define SA_SI_ALL_STREAMBUFFER_ELEMENTS                 0xffffffff


/***********************/
/* STREAM BUFFER FLAGS */
/***********************/

#define SA_SI_STREAM_BEGIN_FLAG                         0x00000001  /* buffer contains the first stream frames */
#define SA_SI_STREAM_END_FLAG                           0x00000002  /* buffer contains the last stream frames */
#define SA_SI_STREAM_SUSPEND_FLAG                       0x00000004  /* buffer contains the last stream frames before suspend */
#define SA_SI_INTERLEAVED_FLAG                          0x00000010  /* storage format is interleaved */
#define SA_SI_STREAM_INCOMPLETE_FLAG                    0x00000020  /* previous data buffer is missing */
#define SA_SI_REFERENCE_LOST_FLAG                       0x00000040  /* data from some sources is possibly wrong */
                                                                    /* this can happen if a d.source was configured with */
                                                                    /* SA_SI_LOWER16ABS_COMPRESSION_MODE enabled, and one of */
                                                                    /* the previous buffers was missing */


/**************/
/* DATA TYPES */
/**************/

/* SI device handle returned by SA_SI_Open */
typedef unsigned int SA_SI_Handle;



/* data buffer info structure.
   Contains information about a data buffer.
   Contained in SA_SI_DataBuffer.
*/
typedef struct
{
    uint32_t bufferId;
    uint32_t frameIndex;            /* stream position of first frame in buffer */
    uint32_t numberOfSources;
    uint32_t numberOfFrames;
    uint32_t flags;                 /* OR'ed stream buffer flags */
} SA_SI_DataBufferInfo;


/* data buffer structure.
   A data buffer holds numberOfFrames frames of numberOfSources data sources.
   data points to an array containing pointers to the data memory.

   If interleaved is 0, each data-source's data is stored in a dedicated
   memory and the array of pointers has the size numberOfSources.
   Access to non-interleaved buffer data for ith data source:
   uint8_t *ptr = buffer->data[i] + framesize * frame_index;

   If interleaved is 1, all data is interleaved in one block of
   memory and the array of pointers has size 1.
   Access to interleaved buffer data for ith data source:
   uint8_t *ptr = buffer->data[0] + framesize * frame_index + value_offset(i);
   where value_offset(i) is the offset (in bytes) of the value from the ith
   data dource in the frame.
   */
typedef struct
{
    SA_SI_DataBufferInfo info;
    uint8_t **data;         // pointer to pointer-array(s): data --> [ptr1,...,ptrN],
                            // where ptr<i> --> uint8[]
} SA_SI_DataBuffer;


/* event structure.
   An instance of SA_SI_Event is an event that has been sent
   from the device or that was generated by the SI library.
   Depending on the event type, different union members are defined.
*/
typedef struct
{
    uint32_t type;
    union {
        uint32_t error;             // error code if the event type is an error event
        uint32_t bufferId;          // id of a buffer if the event has a buffer parameter
        int32_t devEventParameter;  // an event parameter sent from the device (meaning depends on type)
        uint8_t unused[24];
    };
} SA_SI_Event;


/* property key type which encodes a property code and parameters which
   describe a property of the SI device.
   property keys should be encoded with the SA_SI_EPK function. */
typedef uint32_t SA_SI_PropertyKey;



/* returns the library version as a string */
SA_SI_API
const char* SA_SI_CC SA_SI_GetFullVersionString();


/* encodes a property key from property name prop and two parameters p1 and p2 */
SA_SI_API
SA_SI_PropertyKey SA_SI_EPK(uint16_t prop,uint8_t p1,uint8_t p2);


/* writes a list of all sensor devices currently connected to the PC to deviceList.
   every line is a device locator. the lines are separated by a newline. */
SA_SI_API
unsigned int SA_SI_CC SA_SI_EnumerateDevices(const char *options,char *deviceList,size_t *deviceListLen);

/* writes a list of communication interfaces to outBuffer */
SA_SI_API
unsigned int SA_SI_CC SA_SI_EnumerateInterfaces(const char *options,char *outBuffer,size_t *ioBufferSize);


/* opens the sensor device specified in locator.
   (there are currently no configuration options) */
SA_SI_API
unsigned int SA_SI_CC SA_SI_Open(SA_SI_Handle *handle,const char *locator,const char *config);

/* closes a device. automatically frees all streaming buffers associated with
   this device. i.e. accessing a buffer after Close leads to undefined behavior. */
SA_SI_API
unsigned int SA_SI_CC SA_SI_Close(SA_SI_Handle handle);

/* aborts waiting functions like WaitForEvent which will return with SA_SI_CANCELED_ERROR */
SA_SI_API
unsigned int SA_SI_CC SA_SI_Cancel(SA_SI_Handle handle);

/* reads a property value(-array) for the property-key encoded in pk.
   if ioArraySize is a null pointer or *ioArraySize is 1, the value pointer p points
   to one int32_t value. if *ioArraySize is > 1, p is an array of at least *ioArraySize
   int32_t elements.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetProperty_i32(SA_SI_Handle handle,SA_SI_PropertyKey pk,int32_t *value,unsigned int *ioArraySize);

/* writes property value */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetProperty_i32(SA_SI_Handle handle,SA_SI_PropertyKey pk,int32_t value);


/* reads a property value(-array) for the property-key encoded in pk.
   if ioArraySize is a null pointer or *ioArraySize is 1, the value pointer p points
   to one int64_t value. if *ioArraySize is > 1, p is an array of at least *ioArraySize
   int64_t elements.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetProperty_i64(SA_SI_Handle handle,SA_SI_PropertyKey pk,int64_t *value,unsigned int *ioArraySize);

/* writes property value */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetProperty_i64(SA_SI_Handle handle,SA_SI_PropertyKey pk,int64_t value);


/* reads a property value(-array) for the property-key encoded in pk.
   if ioArraySize is a null pointer or *ioArraySize is 1, the value pointer p points
   to one double value. if *ioArraySize is > 1, p is an array of at least *ioArraySize
   double elements.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetProperty_f32(SA_SI_Handle handle,SA_SI_PropertyKey pk,float *value,unsigned int *ioArraySize);

/* writes property value */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetProperty_f32(SA_SI_Handle handle,SA_SI_PropertyKey pk,float value);


/* reads a property value(-array) for the property-key encoded in pk.
if ioArraySize is a null pointer or *ioArraySize is 1, the value pointer p points
to one double value. if *ioArraySize is > 1, p is an array of at least *ioArraySize
double elements.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetProperty_f64(SA_SI_Handle handle,SA_SI_PropertyKey pk,double *value,unsigned int *ioArraySize);

/* writes property value */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetProperty_f64(SA_SI_Handle handle,SA_SI_PropertyKey pk,double value);


/* reads a property value(-array) for the property-key encoded in pk.
   ioArraySize must contain the size of the array 'value' when calling SA_SI_GetProperty_s and
   contains the length of the string when the function returns.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetProperty_s(SA_SI_Handle handle,SA_SI_PropertyKey pk,char *value,unsigned int *ioArraySize);

/* writes property value. value must be a null-terminated string */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetProperty_s(SA_SI_Handle handle,SA_SI_PropertyKey pk,const char *value);



/* returns the channel and the data source index for component selectors
   component ID, component index and data source type.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetDataSource(SA_SI_Handle handle,
    unsigned int componentId,unsigned int componentIndex,unsigned int dsourceType,
    unsigned int *channel, unsigned int *dsourceIndex);



/* returns the current value of a data source as int64 */
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetValue_i64(SA_SI_Handle handle,unsigned int channel,unsigned int dsourceIndex,int64_t *value);


/* returns the current value of a data source as double */
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetValue_f64(SA_SI_Handle handle,unsigned int channel,unsigned int dsourceIndex,double *value);


/* disables all data sources for streaming */
SA_SI_API
unsigned int SA_SI_CC SA_SI_ResetStreamingConfiguration(SA_SI_Handle handle);


/* sets the streaming mode
   the streaming can only be activated to DIRECT_MODE if the final data packet
   from a previous stream has been received.
  */
SA_SI_API
unsigned int SA_SI_CC SA_SI_SetStreamingMode(SA_SI_Handle handle,unsigned int mode);


/* waits for an event */
SA_SI_API
unsigned int SA_SI_CC SA_SI_WaitForEvent(SA_SI_Handle handle,SA_SI_Event *event,unsigned int timeout);


/* acquires a streambuffer for reading data. as long as the buffer is acquired, the caller
   may read data from the buffer. the buffer must be ready before it can be acquired,
   which will be signaled by a streambuffer-ready event. */
SA_SI_API
unsigned int SA_SI_CC SA_SI_AcquireBuffer(SA_SI_Handle handle,unsigned int bufferId,const SA_SI_DataBuffer **buffer);


/* releases an acquired buffer. accessing the buffer data after release will
   cause undefined behavior */
SA_SI_API
unsigned int SA_SI_CC SA_SI_ReleaseBuffer(SA_SI_Handle handle,unsigned int bufferId);

/* returns an info struct for buffer bufferId, which must have been acquired by the caller */
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetBufferInfo(SA_SI_Handle handle,unsigned int bufferId,
    uint32_t *firstFrameIndex,uint32_t *numOfSources,uint32_t *numOfFrames,uint32_t *flags);


/* returns the index of the specified data source in the streaming data buffer.
   for example, if the following data sources are enabled for streaming
   (channel,data source):   (0,0), (1,0), (2,0), (2,9)
    unsigned int index;
    error = SA_SI_GetFrameElementIndex(handle, 2,9, &index);
   would return 3 in index.
   an error is returned, if the requested data source is not enabled for
   streaming.
   the index of the data source may change if data sources are enabled or
   disabled, so this function should only be called after the data stream
   configuration has been completed!
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetFrameElementIndex(SA_SI_Handle handle,
    unsigned int channel,unsigned int dsourceIndex,unsigned int *elementIndex);


/* returns the channel and data source of the nth element in a data stream frame.
   for example, if the following data sources are enabled for streaming
   (channel,data source):   (0,0), (1,0), (2,0), (2,9)
    unsigned int channel, dataSource;
    error = SA_SI_GetFrameElementDataSource(handle, 3, &channel,&dataSource);
   would return 2 in channel and 9 in dataSource.
   an error is returned, if the requested data source is not enabled for
   streaming.
   this function should only be called after the data stream configuration
   has been completed!
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_GetFrameElementDataSource(SA_SI_Handle handle,
    unsigned int elementIndex,unsigned int *channel,unsigned int *dsourceIndex);



/* copies the content of buffer bufferId to user data array dest. the buffer must
   have been acquired with SA_SI_AcquireBuffer.
   the function copies either the whole buffer content if interleaved mode
   is used or the values of one data source in non-interleaved mode.
   in non-interleaved mode elementIndex specifies the element in the frames to be copied.
   in interleaved mode SA_SI_ALL_STREAMBUFFER_ELEMENTS must be passed in elementIndex
   to copy all data sources.
   destSize is the size of the destination buffer in bytes. if destSize is smaller than
   the data to copy, the function returns with SA_SI_QUERYBUFFER_SIZE_ERROR
   and no data is copied to dest.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_CopyBuffer(SA_SI_Handle handle,unsigned int bufferId,unsigned int elementIndex,uint8_t *dest,unsigned int destSize);


/* reads a named data object into buffer.
   ioBufferSize must contain the size of the buffer when calling the function.
   when the function returns, ioBufferSize contains the size of the data that was
   written into the buffer.
   if the buffer is too small for the data object, the function returns with
   SA_SI_QUERYBUFFER_SIZE_ERROR and ioBufferSize contains the required buffer size.
   in that case the content of buffer is invalid.
*/
SA_SI_API
unsigned int SA_SI_CC SA_SI_ReadDataObject(SA_SI_Handle handle,const char *objectName,char *buffer,size_t *ioBufferSize);


/* writes a named data object
   data must contain the object data and dataSize the size of the object data */
SA_SI_API
unsigned int SA_SI_CC SA_SI_WriteDataObject(SA_SI_Handle handle,const char *objectName,const char *data,size_t dataSize);


#ifdef __cplusplus
}
#endif

#endif /* SMARACT_SI_H */
