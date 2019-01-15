#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

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

/*
void appendValue(unsigned int dataSource, void *pValue)
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
    streamData.dataSource[dataSource].data.push_back(v);
}
*/
