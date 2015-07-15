/*
        Thymio-II Firmware

        Copyright (C) 2011 Philippe Retornaz <philippe dot retornaz at epfl dot ch>,
        Mobots group (http://mobots.epfl.ch), Robotics system laboratory (http://lsro.epfl.ch)
        EPFL Ecole polytechnique federale de Lausanne (http://www.epfl.ch)

        See authors.txt for more details about other contributors.

        This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU Lesser General Public License as published
        by the Free Software Foundation, version 3 of the License.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public License
        along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <p24Fxxxx.h>

#include "pmp.h"

void setup_io(void) {
	// Setup PWM high side as opendrain, default high
	_ODE3 = 1;
	_LATE3 = 1;
	_TRISE3 = 0;
	
	_ODE5 = 1;
	_LATE5 = 1;
	_TRISE5 = 0;
	
	_ODE0 = 1;
	_LATE0 = 1;
	_TRISE0 = 0;
	
	_ODE1 = 1;
	_LATE1 = 1;
	_TRISE1 = 0;
	
	// Output pin
	_LATF0 = 1;	// USB-500
	_TRISF0 = 0;
	
	// By default, enable 500mA charging.
	// We will switch to 100mA right after making sure to disable the leds
	_LATF1 = 1; // USB-Charge
	_TRISF1 = 0;
	
	_LATF5 = 0;
	_TRISF5 = 0;	// M1PWML1
	
	_LATB15 = 0;
	_TRISB15 = 0;  // Sound out
	
	_LATC13 = 0;	// LED_CS
	_TRISC13 = 0;
	
	_LATD0 = 0;		// LED CLK, make sure a default level is chosen when spi not enabled
	_TRISD0 = 0;
	
	_LATD4 = 0;
	_TRISD4 = 0; // M2PWML1
	
	_LATD5 = 0;
	_TRISD5 = 0;	// M2PWML2
	
	_LATD6 = 0;
	_TRISD6 = 0;	// ir-pulse-groundL
	
	_LATD8 = 0;		// M1PWML2
	_TRISD8 = 0;
	
	_LATD11 = 0;
	_TRISD11 = 0;	// LED_SDO, make sure it's an output when spi not enabled
	
	_LATE2 = 0; // VA, disabled by default
	_TRISE2 = 0;
	
	_LATE4 = 0;		// ir-pulse-groundR
	_TRISE4 = 0;
	
	_LATF4 = 0;	// ir-pulse-back
	_TRISF4 = 0; 
	
	_LATD9 = 0;	// ir-pulse-front
	_TRISD9 = 0;
	
	
	// Put SD card DAT[3] (CS) at low, then input, will be used for card detection...
	_LATB14 = 0;
	_TRISB14 = 0;
	Nop();
	_TRISB14 = 1;
	_LATB14 = 1;
	
}

void setup_pps(void) {
	/* Output only modules */
	
	// PWM OC
	_RP17R = 19; // output function 19 is OC2 (Table 10-3) Output compare 2; mapped to RP17
	_RP25R = 21; // output function 21 is OC4 (Table 10-3) Output compare 4; mapped to RP25
	_RP20R = 22; // output function 21 is OC5 (Table 10-3) Output compare 5; mapped to RP20
	_RP2R = 20;  // output function 20 is OC3 (Table 10-3) Output compare 3; mapped to RP2
	
	// Sound OC
	_RP29R = 23; // output function 23 is OC6 (Table 10-3) Output compare 6; mapped to RP29
	
	// Led SPI
	_RP11R = 8;  // output function 8 is SCK1OUT (Table 10-3) SPI1 Clock Output; mapped to RP11
    _RP12R = 7;  // output function 7 is SDO1 (Table 10-3) SPI1 Data Output; mapped to RP12
	
	_RP26R = 1;  // output function 1 is C1OUT (Table 10-3) Comparator output 1; mapped to RP26
	
	// OC pulse ir sensors
	_RP10R = 25; // output function 25 is OC8 (Table 10-3) Output compare 8; mapped to RP10
	_RP4R = 24;  // output function 24 is OC7 (Table 10-3) Output compare 7; mapped to RP4
	
	
	/* Input only modules */
	
	// IR Sensors
	_IC1R = 7;   // input function IC1 (Table 10-2) Input capture 1; mapped to RP7
	_IC2R = 27;  // input function IC2 (Table 10-2) Input capture 2; mapped to RP27
	_IC3R = 8;   // input function IC3 (Table 10-2) Input capture 3; mapped to RP8
	_IC4R = 19;  // input function IC4 (Table 10-2) Input capture 4; mapped to RP19
	_IC5R = 9;   // input function IC5 (Table 10-2) Input capture 5; mapped to RP9
	_IC6R = 3;   // input function IC6 (Table 10-2) Input capture 6; mapped to RP3
	_IC7R = 37;  // input function IC7 (Table 10-2) Input capture 7; mapped to RP37
	
	// NTC
	_IC8R = 26;  // input function IC8 (Table 10-2) read through RB13 (ntc.c); mapped to RP26
	
	// IR Remote control
	_IC9R = 26;  // input function IC9 (Table 10-2); mapped to RP26 also
	
	/* Bidirectional modules */
	
	// SD card SPI
	// FIXME Handle correctly VA switchable LDO !!!! 
	// IO not enabled until SPI is enabled, so it's safe 
	// To do it now (TODO: Check this with a scope ... )
	_RP24R = 11; // output function 11 is SCK2OUT (Table 10-3) SPI2 Clock Output; mapped to RP24
    _RP23R = 10; // output function 10 is SDO2 (Table 10-3) SPI2 Data Output; mapped to RP23
	_SDI2R = 22; // input function SDI2 (Table 10-2) SPI2 Data Input; mapped to RP22
    
    // UART rewired by mode_uart
    _U2RXR = 21; // input function U2RX (Table 10-2) UART2 Rx ; mapped to RP21
    _RP16R = 5;  // output function 5 is U2TX (Table 10-3) UART2 Tx; mapped to RP16
}

