//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_C8051F930_Register_Enums.h>                // SFR declarations
#include "variables_globales.h"
#include "pin_test.h"

//-----------------------------------------------------------------------------
//	ADC0_ISR
//-----------------------------------------------------------------------------

INTERRUPT(ADC0_ISR, ADC0EOC_IRQn){

	TEST=!TEST;

}