
/*
	UART_SOFTWARE.c
	
*/


#include "UART_SOFTWARE.h"

///////////////////////////////////////////////////////////////////
//////////  CONFIGURACION DEL TIMER EN MODO FAST PWM  /////////////

void Set_Freq_50Hz(){
	// se configura la senal del servomotor
	
	TCCR0A = 0x82; // salida PWM en PB0
	TCCR0B = 0x19; // modo Fast PWM sin prescalador
	FREQ_SERVO; // frecuencia de 50 Hz
	OCR0A = Centro; // centramos la direccion
	
	// se configura la interrupcion por PCINT2
	
	PCICR = 0x01; //habilita el bloque 0
	PCMSK = 0x04; // habilita entrada en PB2 usando el PCINT2
}

///////////////////////////////////////////////////////////////////
////////////////////  RUTINAS DE INTERRUPCION  ////////////////////

ISR(PCINT0_vect){ //interrupcion por cambio de estado
	PCMSK = 0x00; // deshabilita interrupcion PCINT2
	uint8_t result=0; // variable local para guardar los bits
	
	_delay_us(189); // desfasa la captura a 189 us
	
	for ( uint8_t i=0; i<8; i++){ // inicia la captura de datos
		_delay_us(392); // espera 392 us para el siguiente bit
		if ( PINB & (1<<PINB2)){ // entra si en PB0 hay un "1" logico
			result |=(1<<(i)); // guarda el bit en su posicion correspondiente
		}
	}
	
	_delay_us(392); // espera 392 us para el bit de parada
	if (PINB & (1<<PINB2)){ // si el bit de parada es 1 logico realiza la accion
		if (result==86 || num[0]==86){ // si el dato es igual al inicializador "V" entra
			if (result==87){ // si el dato es el EOF se realiza la accion
				switch ( num[1]){
                    case 68: // caracter D
	                    Derecha; // servomotor a la derecha
						break;
					
					case 70: // caracter F
						Centro; // servomotor al centro
						break;
					
					case 73: // caracter I
						Izquierda; // servomotor a la izquierda
						break;
					
					case 81: // caracter Q
						TRACCION_F; // motor en modo avanzar
						break;
					
					case 80: case 82: // caracter P y R respectivamente
						TRACCION_R; // motor en modo stop y reversa 
						break;
				} // fin de instruccion switch
				conteo_num = 0; // se inicializa en 0
				num[0]=0; // se se inicializa en 0
			} // fin del if del EOF
			else{
				num[conteo_num] = result; // se guarda el valor en el contenedor
				conteo_num++; // se incrementa en 1 la variable  
			}
		} // fin del if SOF
	} // fin del if PINB
	PCMSK = 0x04; // habilita entrada en PB2 usando el PCINT2 
}



//CODIGO PARA RECEPCION DE NUMEROS
/*if (result==88 || num[0]== 88){// SI ES IGUAL AL INICIALIZADOR "X"
	// revisa si el dato recibido esta en el rango de 0(48) a 9(57) y usa un delimitador W(87) y inicializador V(86) datos y X(88)NUMEROS
	// para determinar fin de trama numerica
	
			if (result == 87){ // revisa si el ultimo caracter recibido es "W"
				switch(conteo_num){ //realiza la accion dependiendo de los digitos
					case 4:// tres digitos
					OCR0B = ( (num[1]*100) + (num[2]*10) + num[3] )*(ICR0/100); //  (valor_recibido*ICR0)/100
					break;
					case 3:// dos digitos
					OCR0B = ( (num[1]*10) + num[2] ) *(ICR0/100);
					break;
					case 2:// un digitos
					OCR0B = num[1] *(ICR0/100);
					break;
				}
				conteo_num = 0;// restablece el valor a cero
				num[0]=0;// restablece la primer casilla del arreglo
			}
			else{
				if (conteo_num==0){ // guarda el primer dato recibido
					num[conteo_num]=result;
				}
				else{// de lo contrario guarda el numero en ascii
					num[conteo_num] = result-48; // ascii a numero
				}
				conteo_num++;
			}
			
		}//FIN DEL IF NUMEROS*/