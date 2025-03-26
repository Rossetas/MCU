/*
 * dice.c
 * 
 * Copyright 2025 marco <marco@Ubuntu-VM>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

 #include <pic14/pic12f683.h>

 typedef unsigned int word;

 word __at 0x2007 __CONFIG = (_WDT_OFF & _MCLRE_OFF & _BOREN_OFF); // CONFIG

 #define BTN GP3

 void dice ();

 void delay (unsigned int tiempo);

void main(void)
{
	dice ();
	
}

void dice () {

	GPIO	= 0b00000000; 	// Pines en bajo
	TRISIO	= 0b00001000; 	// PIN P3 - input
	ANSEL	= 0b00000000;	// Puertos como digitales
	CMCON0	= 0b00000111; 	// 111 = CIN pins are configured as I/O, COUT pin is configured as I/O, Comparator output disabled, Comparator off.

	unsigned int timeON = 1000, timeOFF = 100;
	unsigned int seed = 0;

	// Loop forever
	while ( 1 ){
		
		seed = seed + 1;

		if (BTN != 1){

			GPIO = 0b000000;

		}

		if (BTN == 1){

			if (seed == 1){
				GPIO = 0b000001;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}
			
			if (seed == 2){
				GPIO = 0b000010;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}

			if (seed == 3){
				GPIO = 0b000011;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}

			if (seed == 4){
				GPIO = 0b000110;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}

			if (seed == 5){
				GPIO = 0b000111;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}

			if (seed == 6){
				GPIO = 0b010110;
				delay(timeON);
				GPIO = 0b000000;
				delay(timeOFF);
				seed = 0;
				continue;
			}
		}

		if (seed == 6){

			seed = 0; // reinicio del contador
			continue;
			
		}
	}	
}

void delay (unsigned int tiempo){
	
	unsigned int i;
	unsigned int j;

	for(i=0; i<tiempo; i++){
		for(j=0; j<1275; j++){	
		}
	}
}
