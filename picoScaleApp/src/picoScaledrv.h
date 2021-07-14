//-------------------------------- Input parameters --------------------------------
//Channel 0 parameters
#define pos_ch0_longInValueString		"POS_CH0_LONGIN_VAL"
#define scalepos_ch0_longOutValueString	"SCALEPOS_CH0_LONGOUT_VAL"
#define vel_ch0_longInValueString		"VEL_CH0_LONGIN_VAL"
#define acc_ch0_longInValueString		"ACC_CH0_LONGIN_VAL"
#define swraw_ch0_analogInValueString		"SWRAW_CH0_ANALOGIN_VAL"
#define s2wraw_ch0_analogInValueString		"S2WRAW_CH0_ANALOGIN_VAL"
#define sw_ch0_analogInValueString              "SW_CH0_ANALOGIN_VAL"
#define s2w_ch0_analogInValueString             "S2W_CH0_ANALOGIN_VAL"
#define swquality_ch0_analogInValueString       "SWQUALITY_CH0_ANALOGIN_VAL"
#define s2wquality_ch0_analogInValueString	"S2WQUALITY_CH0_ANALOGIN_VAL"
//#define cntrZero_ch0_analogInValueString	"CNTRZERO_CH0_LONGIN_VAL"
//#define cntrOne_ch0_analogInValueString	"CNTRONE_CH0_LONGIN_VAL"
#define envtemp_ch0_longInValueString		"ENVTEMP_CH0_LONGIN_VAL"
#define envHum_ch0_longInValueString		"ENVHUM_CH0_LONGIN_VAL"
#define envPress_ch0_longInValueString          "ENVPRESS_CH0_LONGIN_VAL"
/*#define gpioAdc0_ch0_longInValueString	"GPIOADC0_CH0_ANALOGIN_VAL"
#define gpioAdc1_ch0_longInValueString          "GPIOADC1_CH0_ANALOGIN_VAL"
#define gpioAdc2_ch0_longInValueString          "GPIOADC2_CH0_ANALOGIN_VAL"
#define calcSys0_ch0_longInValueString          "CALCSYS0_CH0_ANALOGIN_VAL"
#define calcSys1_ch0_longInValueString          "CALCSYS1_CH0_ANALOGIN_VAL"
#define calcSys2_ch0_longInValueString          "CALCSYS2_CH0_ANALOGIN_VAL"
#define calcSys3_ch0_longInValueString          "CALCSYS3_CH0_ANALOGIN_VAL"
#define calcSys4_ch0_longInValueString          "CALCSYS4_CH0_ANALOGIN_VAL"
#define calcSys5_ch0_longInValueString          "CALCSYS5_CH0_ANALOGIN_VAL"
#define calcSys6_ch0_longInValueString          "CALCSYS6_CH0_ANALOGIN_VAL"
#define calcSys7_ch0_longInValueString          "CALCSYS7_CH0_ANALOGIN_VAL"*/

//Channel 1 parameters
#define pos_ch1_longInValueString		"POS_CH1_LONGIN_VAL"
#define scalepos_ch1_longOutValueString	"SCALEPOS_CH1_LONGOUT_VAL"
#define vel_ch1_longInValueString		"VEL_CH1_LONGIN_VAL"
#define acc_ch1_longInValueString		"ACC_CH1_LONGIN_VAL"
#define swraw_ch1_analogInValueString		"SWRAW_CH1_ANALOGIN_VAL"
#define s2wraw_ch1_analogInValueString		"S2WRAW_CH1_ANALOGIN_VAL"
#define sw_ch1_analogInValueString              "SW_CH1_ANALOGIN_VAL"
#define s2w_ch1_analogInValueString             "S2W_CH1_ANALOGIN_VAL"
#define swquality_ch1_analogInValueString       "SWQUALITY_CH1_ANALOGIN_VAL"
#define s2wquality_ch1_analogInValueString	"S2WQUALITY_CH1_ANALOGIN_VAL"

//Channel 2 parameters 
#define pos_ch2_longInValueString		"POS_CH2_LONGIN_VAL"
#define scalepos_ch2_longOutValueString	"SCALEPOS_CH2_LONGOUT_VAL"
#define vel_ch2_longInValueString		"VEL_CH2_LONGIN_VAL"
#define acc_ch2_longInValueString		"ACC_CH2_LONGIN_VAL"
#define swraw_ch2_analogInValueString		"SWRAW_CH2_ANALOGIN_VAL"
#define s2wraw_ch2_analogInValueString		"S2WRAW_CH2_ANALOGIN_VAL"
#define sw_ch2_analogInValueString              "SW_CH2_ANALOGIN_VAL"
#define s2w_ch2_analogInValueString             "S2W_CH2_ANALOGIN_VAL"
#define swquality_ch2_analogInValueString       "SWQUALITY_CH2_ANALOGIN_VAL"
#define s2wquality_ch2_analogInValueString	"S2WQUALITY_CH2_ANALOGIN_VAL"

//Communication parameters
#define connectionStatus_binaryInValueString    "CONNECTIONSTATUS_BINARYIN_VAL"
#define streamStatus_binaryInValueString        "STREAMSTATUS_BINARYIN_VAL"
//------------------------------------------------------------------------------------

//-------------------------------- Output parameters ---------------------------------
//Communication parameters
#define framerate_longOutValueString		"FRAMERATE_LONGOUT_VAL"
#define bufferaggr_mbboValueString		"BUFFERAGGR_MBBO_VAL"
#define buffersnum_longOutValueString		"BUFFERSNUM_LONGOUT_VAL"
#define interleaving_binaryOutValueString	"INTERLEAVING_BINARYOUT_VAL"
#define channelindx_mbboValueString		"CHANNELINDX_MBBO_VAL"
#define datasrcindx_mbboValueString		"DATASRCINDX_MBBO_VAL"
#define streamstart_mbboValueString		"STREAMSTART_MBBO_VAL"
#define streamstop_binaryOutValueString         "STREAMSTOP_BINARYOUT_VAL"
#define poll_binaryOutValueString               "POLL_BINARYOUT_VAL"
//------------------------------------------------------------------------------------


//AsynPortDriver variables
#define NUM_ANALOG_IN		28
#define NUM_WAVE_FORM		9
#define NUM_STRING_OUT		1
#define NUM_LONG_OUT		4
#define NUM_MULTIPLE_BIT_OUT	4
#define NUM_BINARY_OUT		1
#define NUM_BINARY_IN		2

#define NUM_PARAMS		70//49
#define MAX_SIGNALS		1	

class PicoScaledrv : public asynPortDriver {
	public:
		PicoScaledrv(const char *portName, const char *ip);
		
		//AsynPortDriver methods extended
		virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);

		//SmarAct's library related
		void picoScale_dataSourcesValues_EPICSRecordsWriting(void *pValue, size_t dataSourceIndex);
		int32_t getDataSize(int32_t dataType);
		unsigned int configureStream(SA_SI_Handle handle);
		void processBuffer(const SA_SI_DataBuffer *buffer);
		unsigned int receiveStreamBuffer(SA_SI_Handle handle, unsigned int timeout, bool &lastFrame);
		void PicoScaleInitializingRoutinesRun();
		void picoScale_open(const char *ip);
		void picoScale_setFramerate();
		void picoScale_stream();
		void picoScale_streamPVA_allChannels();
		void picoScale_streamPosition_allChannels();
		void picoScale_poll();

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

		//--- PicoScale data structures ---
                
                /* Not used so far.
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
		}dataSource;

		/* SmarAct structs to hold streamed data. Not used so far.
                 *  struct DataSourceData_t {
                 *      vector<VariantValue> data;
                 *   };
                 *
                 *  struct StreamData_t {
                 *      vector<DataSourceData_t> dataSource;
                 *   };
                */

		//All stream configurations are stored in streamConfig struct
		struct StreamConfig_t {
		    vector<DataSource_t> enabledDataSources;
		    int32_t frameSize;
		    int32_t interleavingEnabled;
		    int32_t frameAggregation;
		    int32_t streamBufferAggregation;
		    int32_t frameRate;
		    int32_t numberOfStreamBuffers;
		}streamConfig;
                // -------------------------------
                
		//Globals
		bool firstExe = true, lastFrame = false, streamingActive = false;
		unsigned int result; //receives an hex code from every SmarAct function's return that represent success (SA_SI_OK or 0x00) or specific error code (!=SA_SI_OK)
		SA_SI_Handle handle;
		vector<DataSource_t> enabled_singledtsrc_stream, enabled_PVAdtsrcs_stream, enabled_Positiondtsrcs_stream;
		int32_t PVA_frame_size = 0, PositionAllChannels_frame_size = 0; //frame size based on the sum of the datasources' sizes

	protected:
		// --- Input parameters ---
		//Channel 0 parameters
		int pos_ch0_longInValue;
		int scalepos_ch0_longOutValue;
		int vel_ch0_longInValue;
		int acc_ch0_longInValue;
		int swraw_ch0_analogInValue;
		int s2wraw_ch0_analogInValue;
                int sw_ch0_analogInValue;
                int s2w_ch0_analogInValue;
		int swquality_ch0_analogInValue;
		int s2wquality_ch0_analogInValue;
		//int cntrZero_ch0_longInValue;
		//int cntrOne_ch0_longInValue;
		int envtemp_ch0_longInValue;
		int envHum_ch0_longInValue;
		int envPress_ch0_longInValue;
		/*int gpioAdc0_ch0_longInValue;
		int gpioAdc1_ch0_longInValue;
		int gpioAdc2_ch0_longInValue;
		int calcSys0_ch0_longInValue;
		int calcSys1_ch0_longInValue;
		int calcSys2_ch0_longInValue;
		int calcSys3_ch0_longInValue;
		int calcSys4_ch0_longInValue;
		int calcSys5_ch0_longInValue;
		int calcSys6_ch0_longInValue;
		int calcSys7_ch0_longInValue;*/

		//Channel 1 parameters
		int pos_ch1_longInValue;
		int scalepos_ch1_longOutValue;
		int vel_ch1_longInValue;
		int acc_ch1_longInValue;
		int swraw_ch1_analogInValue;
		int s2wraw_ch1_analogInValue;
                int sw_ch1_analogInValue;
                int s2w_ch1_analogInValue;
		int swquality_ch1_analogInValue;
		int s2wquality_ch1_analogInValue;

		//Channel 2 parameters 
		int pos_ch2_longInValue;
		int scalepos_ch2_longOutValue;
		int vel_ch2_longInValue;
		int acc_ch2_longInValue;
		int swraw_ch2_analogInValue;
		int s2wraw_ch2_analogInValue;
                int sw_ch2_analogInValue;
                int s2w_ch2_analogInValue;
		int swquality_ch2_analogInValue;
		int s2wquality_ch2_analogInValue;

		//Communication Parameters
		int connectionStatus_binaryInValue;
                int streamStatus_binaryInValue;
		//--------------------------

		// --- Output parameters ---
		//Communication parameters
		int framerate_longOutValue;
		int bufferaggr_mbboValue;
		int buffersnum_longOutValue;
		int interleaving_binaryOutValue;
		int channelindx_mbboValue;
		int datasrcindx_mbboValue;
		int streamstart_mbboValue;
                int poll_binaryOutValue;
		//--------------------------
};
