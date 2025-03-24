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

 word __at 0x2007 __CONFIG = (_WDT_OFF & _MCLRE_OFF & _BOREN_OFF);

 #define BTN GP3

 void dice ();

 void delay (unsigned int tiempo);

void main(void)
{
	dice ();
	
}

void dice () {

	GPIO	= 0b000000; // Pines en bajo
	TRISIO	= 0b001000; // PIN P3 - input
	ANSEL	= 0b0000000;
	//CMCON0	= ;
	//CMCON1 	= ;
	//VRCON
	// CONFIG

	unsigned int time = 100;
	unsigned int seed = 0;

	// Loop forever
	while ( 1 ){

		//GPIO = 0b0000001;
		//GPIO = 0b1111110;
		//GP0 = 1;
		//GP1 = 0;
		//GP2 = 0;
		//GP4 = 0;

		/*
		seed = seed + 1:

		if (BTN == 1){

			if (seed == 1){

			}
			
			if (seed == 2){

			}

			if (seed == 3){

			}

			if (seed == 4){

			}

			if (seed == 5){

			}

			if (seed == 6){

			}

		}

		if (seed == 6){
			
			seed = 0; // reinicio del contador

		}
		*/
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