/*
 * Coche_Bluetooth_Sonido_Leds.cpp
 *
 * Created: 30/08/2024 05:51:13 p. m.
 * Author : UGB
 */ 

#include "UART_SOFTWARE.c"

/*
    Trama que debe envia el transmisor:
	   +--------+--------+--------+
	   |  SOF   |  DATO  |   EOF  |
       +--------+--------+--------+
	
	donde:
	      SOF = Inicio de trama ('V')
		  DATO = X datos propuestos por el usuario
		  EOF = Fin de trama ('W')
		  
	Acciones que realiza el ATtiny10 con los datos recibidos:
	      'C' = Secuencia de Claxon
		  'Q' = Activacion de motor para Avanzar y leds frontales
		  'R' = Activacion de motor para Retroceder, leds traceros y beep
		  'P' = Desactiva el motor
*/

int main(void){
	sei(); // habilitamos interrupciones globales
	
	TRACCION_F; // controlador del motor en modo stop
	UART_PORT; // se inicializa PB0 y PB1 como salida
	
	PCINT_SET(); // se ajusta la interrupcion por PCINT
	
	while (1) {
		// genera el beep constantemente si esta en modo reversa
		if (num[3] == 82){
			Enable_Beep();
		}
	}
}




