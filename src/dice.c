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

 #define BTN GP3;

 void dice ();

 void delay (unsigned int tiempo);

int main(int argc, char **argv)
{
	dice ();
	
	return 0;
}

void dice () {

	TRISIO |= (0b001000); // PIN P3 - input
	GPIO &= (0b000000); // Pines en bajo
	// ANSEL
	// CMCON
	// CONFIG

	unsigned int time = 100;

	while ( 1 ){

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