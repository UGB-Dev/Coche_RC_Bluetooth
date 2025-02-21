/*
 * Coche_Bluetooth.cpp
 *
 * Created: 10/07/2024 06:25:02 a. m.
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
          'D' = Servomotor gira hacia la Derecha
          'I' = Servomotor gira hacia la Izquierda
          'F' = Servomotor gira hacia el Centro
          'Q' = Activacion de motor para Avanzar
          'R' = Activacion de motor para Retroceder
          'P' = Desactiva el motor
*/


int main(void){
	sei(); // habilitamos interrupciones globales
	
	TRACCION_R;// controlador del motor en modo stop
	UART_PORT; // se inicializa PB0 y PB1 como salida
	Set_Freq_50Hz(); // se ajusta el PWM para la senal del servo motor
	
	while (1) {
	}
}






