
/*
	UART_SOFTWARE.h
	
*/

#define F_CPU 981226UL  
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////
///////////////////  ETIQUETAS PARA ACCIONES  /////////////////////

#define Claxon (ICR0 = (F_CPU / 450 )-1) // 450 Hz
#define Beep (ICR0 = (F_CPU / 2000 )-1)	 // 2 KHz
#define Disable_PWM (DDRB &= ~(1<<PORTB0))
#define Enable_PWM (DDRB |= (1<<PORTB0))

///////////////////////////////////////////////////////////////////
//////////////////  ETIQUETAS PARA LOS PINES  /////////////////////

#define UART_PORT (DDRB|= (1<<PORTB0) | (1<<PORTB1))// salida PB1 y salida pwm en PB0
#define TRACCION_R ( PORTB |= (1<<PORTB1)) // H
#define TRACCION_F ( PORTB &= ~(1<<PORTB1)) // L (IN2 DRIVER)

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

void Enable_Claxon(); // configuracion para el sonido claxon
void Enable_Retroceso(); // configuracion para el sonido beep
void ENA_PWM(); // habilita el modo Fast PWM
void PCINT_SET(); // ajustes de interrupcion PCINT
void Enable_Beep(); // habilita la secuencia de sonido

