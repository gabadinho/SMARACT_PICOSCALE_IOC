#include <iostream>
#include <vector>
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

unsigned int result;

// activate manual adjustment phase
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_AF_ADJUSTMENT_STATE_PROP,0,0),SA_PS_ADJUSTMENT_STATE_MANUAL_ADJUST);
    if (result != SA_SI_OK)
        return result;


