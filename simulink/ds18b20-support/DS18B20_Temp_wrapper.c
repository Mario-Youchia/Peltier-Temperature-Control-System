
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
//Input Code ---------------
#ifndef MATLAB_MEX_FILE

#define ARDUINO 100
#include "Arduino.h"

#include "math.h"

#include "OneWire.h"
#include "OneWire.cpp"
#include "util/OneWire_direct_gpio.h"
#include "util/OneWire_direct_regtype.h"

#include "DallasTemperature.h"
#include "DallasTemperature.cpp"

// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void DS18B20_Temp_Outputs_wrapper(real_T *TempA,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
// Output Code ---------------
//o/p

#ifndef MATLAB_MEX_FILE
if(xD[0] == 1)
{
 // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
 sensors.requestTemperatures(); 
 TempA[0] = sensors.getTempCByIndex(0);
}
#endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void DS18B20_Temp_Update_wrapper(real_T *TempA,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
// Discrete Code / Update Code ---------------
if(xD[0] != 1)
{
 #ifndef MATLAB_MEX_FILE
 // Start up the library
 sensors.begin();
 #endif
 //done with initialization
 xD[0] = 1; 
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}

