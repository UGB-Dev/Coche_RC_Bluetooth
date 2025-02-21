
/*
	UART_SOFTWARE.h
	
*/

#define F_CPU 981226UL 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////
///////////////////  ETIQUETAS PARA ACCIONES  /////////////////////

#define FREQ_SERVO (ICR0 = 19999) // 20 ms (50 Hz)
#define Derecha (OCR0A = 1400) // 76° 1.4 ms
#define Izquierda (OCR0A = 1900) // 103° 1.9 ms
#define Centro (OCR0A = 1650) // 90° 1.65 ms

///////////////////////////////////////////////////////////////////
//////////////////  ETIQUETAS PARA LOS PINES  /////////////////////

#define UART_PORT (DDRB|= (1<<PORTB0) | (1<<PORTB1))// PB0 como PWM y PB1 como salida
#define TRACCION_R ( PORTB &= ~ (1<<PORTB1)) // L (IN1 DRIVER)
#define TRACCION_F ( PORTB |= (1<<PORTB1)) // H (IN1 DRIVER)

/*
     Tabla de verdad  Driver Puente H BA6956AN
      +------------+------------+------------+
      |  FIN(IN1)  |  RIN(IN2)  | OPERACION  |
      +------------+------------+------------+
      |     H      |     L      |  Avanzar   |
      +------------+------------+------------+
      |     L      |     H      |  Reversa   |
      +------------+------------+------------+
      |     L      |     L      |  Inactivo  |
      +------------+------------+------------+
	  
            Tabla de verdad ATtiny10 
      +------------+------------+------------+
      |  ATtiny 1  |  ATtiny 2  | OPERACION  |
	  |   ( PB1 )  |   ( PB1 )  |            |
      +------------+------------+------------+
      |     H      |     L      |  Avanzar   |
      +------------+------------+------------+
      |     L      |     H      |  Reversa   |
      +------------+------------+------------+
      |     L      |     L      |  Inactivo  |
      +------------+------------+------------+ 
	  
*/

///////////////////////////////////////////////////////////////////
/////////////////////  VARIABLES GLOBALES  ////////////////////////

uint8_t num[4]; //contenedor de datos de entrada
uint8_t conteo_num=0; // variable de conteo de datos

///////////////////////////////////////////////////////////////////
////////////////////  FUNCIONES PROTOTIPO  ////////////////////////

void Set_Freq_50Hz(); // inicializacion de PWM para servomotor