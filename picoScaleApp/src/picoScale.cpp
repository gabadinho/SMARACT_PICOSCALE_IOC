#include <stdioLib.h>
#include <vector>
#include <iostream>

using namespace std;





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




int main(argc, char* argv[]){

	unsigned int result;

}
