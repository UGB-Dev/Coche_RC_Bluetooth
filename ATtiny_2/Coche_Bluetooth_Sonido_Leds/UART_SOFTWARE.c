
/*
	UART_SOFTWARE.c
	
*/

#include "UART_SOFTWARE.h"

///////////////////////////////////////////////////////////////////
//////////  CONFIGURACION DEL TIMER EN MODO FAST PWM  /////////////

void ENA_PWM(){ 
	Enable_PWM;
	TCCR0A = 0x82; // salida PWM en PB0
	TCCR0B = 0x19; // modo Fast PWM sin prescalador
}

///////////////////////////////////////////////////////////////////
/////////////  CONFIGURACION DE INTERRUPCION PCINT  ///////////////

void PCINT_SET(){
	// interrupcion por PCINT2
	PCICR = 0x01; //habilita el bloque 0
	PCMSK = 0x04; // habilita como entrada pcint2 PB2
}

///////////////////////////////////////////////////////////////////
/////////////  CONFIGURACION DE SONIDO BEEP Y CLAXON  /////////////

void Enable_Claxon(){ // 400Hz (2.5 ms) Claxon 12.51 ms
	ENA_PWM();
	Claxon; // TOP DE PWM
	OCR0A = ICR0>>1; // TOP/2 DE PWM
	DDRB |= (1<<PORTB0);// CON SALIDA EN PB0
	_delay_ms(100);
	DDRB &= ~(1<<PORTB0);// SIN SALIDA EN PB0
	_delay_ms(100);
	DDRB |= (1<<PORTB0);// CON SALIDA EN PB0
	_delay_ms(500);
	DDRB &= ~(1<<PORTB0);// SIN SALIDA EN PB0
}

void Enable_Retroceso(){
	ENA_PWM(); // se habilita PWM
	Beep; // ajuste de la senal a 2 KHz
	OCR0A = ICR0>>1; // senal de 50%
}

void Enable_Beep(){
	Enable_PWM; // se habilita PWM
	_delay_ms(300);
	Disable_PWM; // se deshabilita PWM
	_delay_ms(300);
}

///////////////////////////////////////////////////////////////////
////////////////////  RUTINAS DE INTERRUPCION  ////////////////////

ISR(PCINT0_vect){ //interrupcion por cambio de estado
	PCMSK = 0x00;// deshabilita interrupcion PCINT2
	uint8_t result=0; // variable local para guardar los bits
	
	_delay_us(189); // desfasa la captura a 189 us
	
	for ( uint8_t i=0; i<8; i++){ // inicia captura de datos
		_delay_us(392); // espera 392 us para el siguiente bit
		if ( PINB & (1<<PINB2)){ // entra si en PB0 hay un "1" logico
			result |=(1<<(i)); // guarda el bit en su posicion correspondiente
		}
	}
	
	_delay_us(392); // espera 392 us para el bit de parada

	if (PINB & (1<<PINB2)){ // si el bit de parada es 1 logico realiza la accion
		if (result==86 || num[0]==86){ // si es igual a inicializador "V" entra
			
			if (result==87){// si el dato es el EOF se realiza la accion
				switch ( num[1]){
					case 67: //  caracter C
						Enable_Claxon(); // sonido del claxon
						break;
					
					case 81: //	 caracter Q
						Disable_PWM;
						num[3]=81; // auxiliar para determinar modo avanzar
						TRACCION_F; // motor en modo avanzar	
						break;
					
					case 82: //  caracter R
					    num[3]=82; // auxiliar para determinar modo reversa
						TRACCION_R; // motor en modo reversa
						Enable_Retroceso(); // sonido de reversa y habilita motor
						break;
					
					case 80: // caracter P
						Disable_PWM;
						TRACCION_R; // se mantiene pb1 activo todo el tiempo
						break;
				}
				
				conteo_num = 0; // se se inicializa en 0
				num[0] = 0; // se guarda el valor en el contenedor
			}  // fin del if del EOF
			else{
				num[conteo_num] = result; // se guarda el valor en el contenedor
				conteo_num++; // se incrementa en 1 la variable
			}
			
		} // fin del if SOF
	}// fin de if PINB
	PCMSK = 0x04;
}// fin de ISR


