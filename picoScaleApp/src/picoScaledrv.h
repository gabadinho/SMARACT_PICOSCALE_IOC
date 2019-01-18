//-------------------------------- Input parameters --------------------------------
//Channel 0 parameters
#define pos_ch0_waveformValueString		"POS_CH0_WAVEFORM_VAL"
#define vel_ch0_waveformValueString		"VEL_CH0_WAVEFORM_VAL"
#define acc_ch0_waveformValueString		"ACC_CH0_WAVEFORM_VAL"
#define swraw_ch0_analogInValueString		"SWRAW_CH0_ANALOGIN_VAL"
#define s2wraw_ch0_analogInValueString		"S2WRAW_CH0_ANALOGIN_VAL"
#define swquality_ch0_analogInValueString	"SWQUALITY_CH0_ANALOGIN_VAL"
#define s2wquality_ch0_analogInValueString	"S2WQUALITY_CH0_ANALOGIN_VAL"
#define cntrZero_ch0_analogInValueString	"CNTRZERO_CH0_ANALOGIN_VAL"
#define cntrOne_ch0_analogInValueString		"CNTRONE_CH0_ANALOGIN_VAL"
#define envtemp_ch0_analogInValueString		"ENVTEMP_CH0_ANALOGIN_VAL"
#define envHum_ch0_analogInValueString		"ENVHUM_CH0_ANALOGIN_VAL"
#define envPress_ch0_analogInValueString	"ENVPRESS_CH0_ANALOGIN_VAL"
#define gpioAdc0_ch0_analogInValueString	"GPIOADC0_CH0_ANALOGIN_VAL"
#define gpioAdc1_ch0_analogInValueString	"GPIOADC1_CH0_ANALOGIN_VAL"
#define gpioAdc2_ch0_analogInValueString	"GPIOADC2_CH0_ANALOGIN_VAL"
#define calcSys0_ch0_analogInValueString	"CALCSYS0_CH0_ANALOGIN_VAL"
#define calcSys1_ch0_analogInValueString	"CALCSYS1_CH0_ANALOGIN_VAL"
#define calcSys2_ch0_analogInValueString	"CALCSYS2_CH0_ANALOGIN_VAL"
#define calcSys3_ch0_analogInValueString	"CALCSYS3_CH0_ANALOGIN_VAL"
#define calcSys4_ch0_analogInValueString	"CALCSYS4_CH0_ANALOGIN_VAL"
#define calcSys5_ch0_analogInValueString	"CALCSYS5_CH0_ANALOGIN_VAL"
#define calcSys6_ch0_analogInValueString	"CALCSYS6_CH0_ANALOGIN_VAL"
#define calcSys7_ch0_analogInValueString	"CALCSYS7_CH0_ANALOGIN_VAL"

//Channel 1 parameters
#define pos_ch1_waveformValueString		"POS_CH1_WAVEFORM_VAL"
#define vel_ch1_waveformValueString		"VEL_CH1_WAVEFORM_VAL"
#define acc_ch1_waveformValueString		"ACC_CH1_WAVEFORM_VAL"
#define swraw_ch1_analogInValueString		"SWRAW_CH1_ANALOGIN_VAL"
#define s2wraw_ch1_analogInValueString		"S2WRAW_CH1_ANALOGIN_VAL"
#define swquality_ch1_analogInValueString	"SWQUALITY_CH1_ANALOGIN_VAL"
#define s2wquality_ch1_analogInValueString	"S2WQUALITY_CH1_ANALOGIN_VAL"

//Channel 2 parameters 
#define pos_ch2_waveformValueString		"POS_CH2_WAVEFORM_VAL"
#define vel_ch2_waveformValueString		"VEL_CH2_WAVEFORM_VAL"
#define acc_ch2_waveformValueString		"ACC_CH2_WAVEFORM_VAL"
#define swraw_ch2_analogInValueString		"SWRAW_CH2_ANALOGIN_VAL"
#define s2wraw_ch2_analogInValueString		"S2WRAW_CH2_ANALOGIN_VAL"
#define swquality_ch2_analogInValueString	"SWQUALITY_CH2_ANALOGIN_VAL"
#define s2wquality_ch2_analogInValueString	"S2WQUALITY_CH2_ANALOGIN_VAL"
//------------------------------------------------------------------------------------

//-------------------------------- Output parameters ---------------------------------
//Communication parameters
#define ip_stringOutValueString			"IP_STRINGOUT_VAL"
#define framerate_longOutValueString		"FRAMERATE_LONGOUT_VAL"
#define bufferaggr_mbboValueString		"BUFFERAGGR_MBBO_VAL"
#define buffersnum_longOutValueString		"BUFFERSNUM_LONGOUT_VAL"
#define interleaving_boValueString		"INTERLEAVING_BO_VAL"
#define channelindx_mbboValueString		"CHANNELINDX_MBBO_VAL"
#define datasrcindx_mbboValueString		"DATASRCINDX_MBBO_VAL"

//Adjustment parameters
#define workingdistmin_longOutValueString	"WORKINGDISTMIN_LONGOUT_VAL"
#define workingdistmax_longOutValueString	"WORKINGDISTMAX_LONGOUT_VAL"
//------------------------------------------------------------------------------------


//AsynPortDriver variables
#define NUM_ANALOG_IN		28
#define NUM_WAVE_FORM		9
#define NUM_STRING_OUT		1
#define NUM_LONG_OUT		3
#define NUM_MULTIPLE_BIT_OUT	4
#define NUME_BINARY_OUT		1

#define NUM_PARAMS		46
#define MAX_SIGNALS		1	

using namespace std;

//static const char *driverName = "picoScaledrv";	

class PicoScaledrv : public asynPortDriver {
	public:
		PicoScaledrv();
		PicoScaledrv(const char *portName);

		//gets
		virtual void getIp_stringOutValue(char *locator);
		virtual void getChannelindx_mbboValue(int *channelIndex);
		virtual void getDatasrcindx_mbboValue(int *datasrcIndex);
		virtual void getInterleaving_boValue(int *interleavingMode);
		virtual void getBufferaggr_mbboValue(int *bufferAggr);
		virtual void getBuffersnum_longOutValue(int *buffersNum);
	
		//sets
		virtual void setFramerate_longOutValue(int frameRate);

	protected:
		// --- Input parameters ---
		//Channel 0 parameters
		int pos_ch0_waveformValue;
		int vel_ch0_waveformValue;
		int acc_ch0_waveformValue;
		int swraw_ch0_analogInValue;
		int s2wraw_ch0_analogInValue;
		int swquality_ch0_analogInValue;
		int s2wquality_ch0_analogInValue;
		int cntrZero_ch0_analogInValue;
		int cntrOne_ch0_analogInValue;
		int envtemp_ch0_analogInValue;
		int envHum_ch0_analogInValue;
		int envPress_ch0_analogInValue;
		int gpioAdc0_ch0_analogInValue;
		int gpioAdc1_ch0_analogInValue;
		int gpioAdc2_ch0_analogInValue;
		int calcSys0_ch0_analogInValue;
		int calcSys1_ch0_analogInValue;
		int calcSys2_ch0_analogInValue;
		int calcSys3_ch0_analogInValue;
		int calcSys4_ch0_analogInValue;
		int calcSys5_ch0_analogInValue;
		int calcSys6_ch0_analogInValue;
		int calcSys7_ch0_analogInValue;

		//Channel 1 parameters
		int pos_ch1_waveformValue;
		int vel_ch1_waveformValue;
		int acc_ch1_waveformValue;
		int swraw_ch1_analogInValue;
		int s2wraw_ch1_analogInValue;
		int swquality_ch1_analogInValue;
		int s2wquality_ch1_analogInValue;

		//Channel 2 parameters 
		int pos_ch2_waveformValue;
		int vel_ch2_waveformValue;
		int acc_ch2_waveformValue;
		int swraw_ch2_analogInValue;
		int s2wraw_ch2_analogInValue;
		int swquality_ch2_analogInValue;
		int s2wquality_ch2_analogInValue;
		//--------------------------

		// --- Output parameters ---
		//Communication parameters
		int ip_stringOutValue;
		int framerate_longOutValue;
		int bufferaggr_mbboValue;
		int buffersnum_longOutValue;
		int interleaving_boValue;
		int channelindx_mbboValue;
		int datasrcindx_mbboValue;

		//Adjustment parameters
		int workingdistmin_longOutValue;
		int workingdistmax_longOutValue;
		//--------------------------
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

//Globals
PicoScaledrv *picoScaledrv;
unsigned int result;
SA_SI_Handle handle;
struct StreamConfig_t streamConfig;
const SA_SI_DataBuffer *pBuffer;
int32_t dataSourceP0, dataSourceV0, dataSourceA0, dataSourceP1, dataSourceV1, dataSourceA1, dataSourceP2, dataSourceV2, dataSourceA2;
vector<int32_t> stream_datasrcs_sizes, streamPVA_allchannels_datasrcs_sizes, streamPosition_allchannels_datasrcs_sizes;
int32_t streamPVA_allchannels_frame_size = 0, streamPosition_allchannels_frame_size = 0;

//SmarAct library calls
unsigned int picoScale_open(struct subRecord *psub);
unsigned int picoScale_close(struct subRecord *psub);
unsigned int picoScale_setFramerate(struct subRecord *psub);
unsigned int picoScale_stream(genSubRecord *pgenSub);
unsigned int picoScale_streamPVA_allChannels(genSubRecord *pgenSub);
unsigned int picoScale_streamPosition_allChannels(genSubRecord *pgenSub);
unsigned int picoScale_poll(struct subRecord *psub);
unsigned int picoScale_adjust(struct subRecord *psub);
