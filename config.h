//
// Created by SQ5RWU on 2016-12-24.
//

#ifndef STM32_RTTY_CONFIG_H
#define STM32_RTTY_CONFIG_H

#ifdef USE_EXTERNAL_CONFIG
#include "config_external.h"
#else

//**************config**************
#define CALLSIGN "NO1LIC-1" // put your callsign here
#define APRS_CALLSIGN "SQ7FJB-11"
//#define APRS_CALLSIGN(a,b) a ## b

#define APRS_SSID 0 // 'B'
#define APRS_COMMENT "N0LIC TEAM"



#define No_Fox	 1	// ile lisów jest rozstawionych bez MO
#define Fox 6 // 0- MOE, 1 -MOI, 2- MOS, 3- MOH, 4 - MO5 5 -  MO //- który lis 6..17 (H1..H12)szukacze tylko aprs
#define Cycle_Fox  (No_Fox - (No_Fox - Fox))

//#define APRS_SSID Fox

//#define APRS_SYMBOL "/$"

#if Fox == 0
#define APRS_SYMBOL "/1"
	//#define APRS_SYMBOL "/\0x5c"

#elif Fox == 1
	#define APRS_SYMBOL "/2"

#elif Fox == 2
	#define APRS_SYMBOL "/3"

#elif Fox == 3
	#define APRS_SYMBOL "/4"

#elif Fox == 4
	#define APRS_SYMBOL "/5"

#elif Fox == 5
	#define APRS_SYMBOL "/6"

#elif Fox == 6
	#define APRS_SYMBOL "/["

#elif Fox == 7
	#define APRS_SYMBOL "/["

#elif Fox == 8
	#define APRS_SYMBOL "/["

#elif Fox == 9
	#define APRS_SYMBOL "/["

#elif Fox == 10
	#define APRS_SYMBOL "/["

#elif Fox == 11
	#define APRS_SYMBOL "/["

#elif Fox == 12
	#define APRS_SYMBOL "/["

#elif Fox == 13
	#define APRS_SYMBOL "/["
#elif Fox == 14
	#define APRS_SYMBOL "/["
#elif Fox == 15
	#define APRS_SYMBOL "/["
#elif Fox == 16
	#define APRS_SYMBOL "/["
#elif Fox == 17
	#define APRS_SYMBOL "/["

#else
	#define APRS_SYMBOL "/["


#endif


#define RTTY_TO_APRS_RATIO 1

//*************frequency********************
#define RTTY_FREQUENCY  434.500f //Mhz middle frequency
#define APRS_FREQUENCY  434.400f //432.498f //Mhz middle frequency
#define ACW_FREQUENCY  434.500f //432.498f //Fox's Mhz middle frequency
#define ACW_MO_FREQUENCY  434.550f //432.498f //Fox MO Mhz middle frequency

//************rtty speed****************** si4032
#define RTTY_SPEED  2500
// SHITY -> 450Hz
//************rtty bits****************** si4032
#define RTTY_7BIT   1
//************rtty stop bits****************** si4032
#define RTTY_USE_2_STOP_BITS   0
//********* power definition**************************
#define Smoc  0 // PWR 0...7 0- MIN ... 7 - MAX
// 7 -> 42.95 mW@434.150 MHz na E4406A
//***************************************************
// WARNING: do not use this in flying tracker!
#define ALLOW_DISABLE_BY_BUTTON 1
//********** frame delay in msec**********
#define tx_delay  5000







#endif


#endif //STM32_RTTY_CONFIG_H
