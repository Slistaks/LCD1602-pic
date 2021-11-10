

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef lcd_lib
#define	lcd_lib

#include <xc.h> // include processor files - each processor file is guarded.  
/*
   Conexiones:
   MICROCONTROLADOR    ->     DISPLAY
 
           RB0         ->       RS
           RB1         ->       RW  (se puede no conectar,poniendo a gnd)
           RB2         ->       e_e
           RB3         ->       NO CONECTA (para usarse, modificar codigo)
           RB4         ->       DB4
           RB5         ->       DB5
           RB6         ->       DB6
           RB7         ->       DB7
 
 PROBADO 30/12/19 -> FUNCIONA
 
    NOTAS:
         USAR INI_LCD(). NO USAR LCD_INI().
         LOS CABLES QUE ENTRAN AL LCD APARENTEMENTE ESTAN BIEN,
         PERO NO LO ESTAN. SI NO ANDA TOCAR LOS CABLES DEL LCD (NO LOS DEL uC)
         MIENTRAS SE INICIALIZA EL LCD, UNA VEZ INICIALIZADO SIGUE ANDANDO BIEN
         SIN NECESIDAD DE ASISTIR A LOS CABLES.
  
  
 PROBAR LECTURA DE DISPLAY (LEER REGISTROS DEL DISPLAY), CHEQUEAR ANTES QUE
 LOS PINES DEL uC SE PONGAN EN ALTA IMPEDANCIA ANTES DE PONER EL LCD EN MODO
 LECTURA.
 
 OPTIMIZAR DELAY, ESTA IMPLEMENTADO COMO MACRO, REEMPLAZAR POR FUNCION.
 
 Modulos usados: 0.
 
 */

#define _XTAL_FREQ 20000000

#define PORTLCD PORTB       //modificar la B por el puerto a usar
#define TRISPORTLCD_rw TRISB1       //tiene que coincidir con rw
#define TRISPORTLCD TRISB       //modificar la B por el puerto a usar
#define rs  RB0
#define rw  RB1//para usar display normal, poner en escritura y no gastar gpio.
#define e_e RB2
#define db4 RB4
#define db5 RB5
#define db6 RB6
#define db7 RB7

#define linea_2 0x40
#define linea_1 0x00

#define bus_display 0 //0->4 bits, 1->8 bits        |no implementado, terminar
#define lineas_display 1 //1->2 lineas, 0->1 linea  |se inicializa en 2 lineas 
#define fuente_display 0 //0->5x8 puntos, 1->5x10 puntos|y F=5x8 siempre creo
                                                  //    |y 4-bit interfaz
void ini_lcd(void); //usar este
void lcd_ini(void); //no usar
void print(char s[]);
void print_var(unsigned char var);
void display_ins(unsigned int data);
void display_cursor_blink(unsigned char d, unsigned char c, unsigned char b);
void clear_display();
void incdec_shift(unsigned char i_d, unsigned char s);
void function_set();
void set_cgram_adress(unsigned char adress);
void set_ddram_adress(unsigned char adress);
void dd_cg_write(unsigned char data);
void enviar(unsigned int instr);
void enable(void);
unsigned int instruccion;



#endif	/* XC_HEADER_TEMPLATE_H */

