#include        <types.h>
#include        <dbDefs.h>
#include        <subRecord.h>
#include        <dbCommon.h>
#include        <recSup.h>
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

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
