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
#include <avr/interrupt.h>  // Interrupts
//#include <util/delay.h>

/* function prototype */
void traffic_light();
void FSM();
void delay(unsigned int);
/* ********** */

int main(void)
{
  traffic_light();
}

void traffic_light(){

  // Registers Config
  //SREG = 0x;

  // config ports
  DDRB = 0xF9;  // pins B
  DDRA = 0x03;   // pins A

  // https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html

  // interruptions
  GIMSK |= (1 << PCIE0); // //Se habilita la interrupcion por PCIE0
  PCMSK0 |= 0x06; // PB1 - PB2 as irq buttons

  // timers
  TCCR0A |= 0x00; // Mode: normal
  TCCR0B |= 0x04; // 256 (From prescaler)
  TCNT0 = 0x00;   // Inicializa el contador del Timer 0 a 0
  TIMSK0 |= (1 << TOIE0); // Habilita la interrupción por desbordamiento del Timer0

  sei(); // enable irq global 

  while ( 1 ){

    FSM();

  }

}

void FSM(){

}

void delay(unsigned int overflows){

}

ISR(PCINT0_vect) {
  // Aquí puedes manejar la interrupción de PB1 o PB2
  // Para determinar cuál de los botones fue presionado, puedes leer el estado de los pines
  if (PINB & (1 << PB1)) {
      // Si PB1 está presionado, realiza lo que necesites para ese botón
  }

  if (PINB & (1 << PB2)) {
      // Si PB2 está presionado, realiza lo que necesites para ese botón
  }
}

ISR(TIMER0_OVF_vect){

}





/*
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0x08; //Configuracion del puerto

  //Parpadear
  while (1) {
    PORTB = 0x00; //PORTB &= ~(1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(500); 
    PORTB = 0x08; //PORTB |=  (1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(500); 
  }
}
*/