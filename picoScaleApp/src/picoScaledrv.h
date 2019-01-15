static const char *driverName = "picoScaledrv";

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

class PicoScaledrv : public asynPortDriver {
	public:
		PicoScaledrv(const char *portName);

		//SmarAct library calls
		virtual unsigned int picoScale_open(struct subRecord *psub);
		virtual unsigned int picoScale_close(struct ubRecord *psub);
		virtual unsigned int picoScale_setFramerate(struct subRecord *psub){
		virtual unsigned int picoScale_stream(genSubRecord *pgenSub);
		virtual unsigned int picoScale_streamPVA(genSubRecord *pgenSub);
		virtual unsigned int picoScale_streamPosition_allChannels(genSubRecord *pgenSub);
		virtual unsigned int picoScale_poll(struct subRecord *psub);
		virtual unsigned int picoScale_adjust(struct subRecord *psub);
		
	protected:
		// --- Input parameters ---
		//Channel 0 parameters
		vector<double> pos_ch0_waveformValue[];
		vector<double> vel_ch0_waveformValue[];
		vector<double> acc_ch0_waveformValue[];
		double swraw_ch0_analogInValue;
		double s2wraw_ch0_analogInValue;
		double swquality_ch0_analogInValue;
		double s2wquality_ch0_analogInValue;
		double cntrZero_ch0_analogInValue;
		double cntrOne_ch0_analogInValue;
		double envtemp_ch0_analogInValue;
		double envHum_ch0_analogInValue;
		double envPress_ch0_analogInValue;
		double gpioAdc0_ch0_analogInValue;
		double gpioAdc1_ch0_analogInValue;
		double gpioAdc2_ch0_analogInValue;
		double calcSys0_ch0_analogInValue;
		double calcSys1_ch0_analogInValue;
		double calcSys2_ch0_analogInValue;
		double calcSys3_ch0_analogInValue;
		double calcSys4_ch0_analogInValue;
		double calcSys5_ch0_analogInValue;
		double calcSys6_ch0_analogInValue;
		double calcSys7_ch0_analogInValue;

		//Channel 1 parameters
		vector<double> pos_ch1_waveformValue[];
		vector<double> vel_ch1_waveformValue[];
		vector<double> acc_ch1_waveformValue[];
		double swraw_ch1_analogInValue;
		double s2wraw_ch1_analogInValue;
		double swquality_ch1_analogInValue;
		double s2wquality_ch1_analogInValue;

		//Channel 2 parameters 
		vector<double> pos_ch2_waveformValue[];
		vector<double> vel_ch2_waveformValue[];
		vector<double> acc_ch2_waveformValue[];
		double swraw_ch2_analogInValue;
		double s2wraw_ch2_analogInValue;
		double swquality_ch2_analogInValue;
		double s2wquality_ch2_analogInValue;
		//--------------------------

		// --- Output parameters ---
		//Communication parameters
		char ip_stringOutValue[15];
		unsigned short framerate_longOutValue;
		unsigned short bufferaggr_mbboValue;
		unsigned short buffersnum_longOutValue;
		bool interleaving_boValue;
		unsigned short channelindx_mbboValue;
		unsigned short datasrcindx_mbboValue;

		//Adjustment parameters
		unsigned short workingdistmin_longOutValue;
		unsigned short workingdistmax_longOutValue;
		//--------------------------

	private:
		//PicoScale variables
		unsigned int result;
    		SA_SI_Handle handle;
}
