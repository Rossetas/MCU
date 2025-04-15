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

/* function prototype */
void traffic_light();
void FSM();
void start_delay(uint16_t);
/* ********** */

/* global variables */
volatile uint8_t request = 0;
unsigned int state = 0, next_state = 0;
volatile uint8_t en_delay = 0;
volatile uint16_t times = 0;
volatile uint16_t target_times = 0;
volatile uint8_t delay_done = 0;
/* ********** */

/* states FSM */
#define paso_vehiculos  0
#define waiting         1
#define paso_peatones   2
/* ********** */

int main(void)
{
  traffic_light();
}

void traffic_light(){

  // config ports
  DDRB = 0xF9;  // pins B
  DDRA = 0x03;  // pins A

  // interruptions
  GIMSK |= (1 << PCIE0);  // Se habilita la interrupcion por PCIE0
  PCMSK |= 0x06;          // PB1 - PB2 as irq buttons

  // timers
  TCCR0A |= 0x00; // Mode: normal
  TCCR0B |= 0x04; // 256 (From prescaler)
  TCNT0 = 0x00;   // Inicializa el contador del Timer 0 a 0

  sei(); // enable irq global
  
  next_state = paso_vehiculos;

  while ( 1 ){

    FSM();

  }
}

void FSM(){

  state = next_state;

  switch(state){

    case paso_vehiculos:
        // vehiculos en verde
        PORTB = (1 << PB5) | (1 << PB6);  // Verde vehiculo + Rojo peatones izquierdos
        PORTA = (1 << PA0);               // Rojo peatones derechos
        start_delay(1221);                // 10 segundos = 1221 overflows @8MHz, prescaler 256

        while (!delay_done); // Espera con interrupciones

        if (request) {
          request = 0;
          next_state = waiting;
        } else {
          next_state = paso_vehiculos;
        }

    break;

    case waiting:
        // vehiculos en amarillo
        PORTB = (1 << PB4) | (1 << PB6);  // Amarillo vehiculo + Rojo peatones izquierdos
        PORTA = (1 << PA0);               // Rojo peatones derechos
        start_delay(366);                 // 3 segundos = 366 overflows

        while (!delay_done);

        next_state = paso_peatones;

    break;

    case paso_peatones:
        // peatones en verde
        PORTB = (1 << PB3);              // Rojo vehiculo
        PORTB |= (1 << PB7);             // Verde peatones izquierdos
        PORTA = (1 << PA1);              // Verde peatones derechos
        start_delay(1221);               // 10 segundos

        while (!delay_done);

        // despues del paso peatonal
        next_state = paso_vehiculos;
        PCMSK |= (1 << PCINT1) | (1 << PCINT2);  // Reactivar interrupciones

    break;

    default:
        next_state = paso_vehiculos;

    break;

  }
}

void start_delay(uint16_t overflows){

  en_delay = 1;
  delay_done = 0;
  times = 0;
  target_times = overflows;
  TIMSK |= (1 << TOIE0);      // Habilitar interrupcion por overflow

}

ISR(PCINT0_vect){

  if ((PINB & (1 << PB1)) || (PINB & (1 << PB2))){
    request = 1;
    PCMSK &= ~((1 << PCINT1) | (1 << PCINT2));    // Se desactiva la interrupcion para evitar multiples activaciones
  }
}

ISR(TIMER0_OVF_vect){

  if (en_delay){
    times++;
    if (times >= target_times){
      en_delay = 0;
      delay_done = 1;
      TIMSK &= ~(1 << TOIE0); // Desactivar solo la interrupcion TOIE0
    }
  }
}
