/*
 * traffic_light.c
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


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0x08; //Configuracion del puerto

  //Parpadear
  while (1) {
    PORTB = 0x00; //PORTB &= ~(1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(1000); 
    PORTB = 0x08; //PORTB |=  (1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(1000); 
  }
}