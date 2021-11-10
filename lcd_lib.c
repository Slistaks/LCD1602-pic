/*
 * File:   lcd_lib.c
 * Author: juan_
 *
 * Created on 25 de mayo de 2020, 23:26
 */

#include "lcd_lib.h"
#include <xc.h>

void lcd_ini(){
    
    PORTLCD=0b100; //+era 0
    TRISPORTLCD=0;  
    
    __delay_ms(50); //esperar que se estabilice el display
    //INICIALIZACION INICIALIZACION INICIALIZACION INICIALIZACION
    
    //-----------------------------------
    PORTLCD=0b00110100; //+
    enable();                                  //function set 1
    __delay_ms(5);      //>4.1ms
    //-----------------------------------
    PORTLCD=0b00110100;  //+
    enable();                                  //function set 2
    __delay_us(150);    // >100us
    //-----------------------------------
    PORTLCD=0b00110100;  //+
    enable();                                  //function set 3
    __delay_us(150);    //no dice cuanto
    //-----------------------------------
    PORTLCD=0b00100100;  //+
    enable();                                  //function set 4
    __delay_ms(1);  // a ojo
    //-----------------------------------
    PORTLCD=0b00100100;  //+                       //function set 5 H
    enable();
    PORTLCD=0b10000100;  //+                        //function set 5 L NF000000
    enable();
    __delay_ms(1);
    //-----------------------------------
    PORTLCD=0b00000100;  //+                       //Display control H
    enable();
    PORTLCD=0b10000100;  //+  //Display control L   1DCB0000 ->modificar a gusto?
    enable();
    __delay_ms(1);
    //------------------------------------
    PORTLCD=0b00000100;  //+  //Display clear H
    enable();
    PORTLCD=0b00010100;  //+   //Display clear L
    enable();
    __delay_ms(2);
    //------------------------------------
    PORTLCD=0b00000100;  //+   //Entry mode set H
    enable();
    PORTLCD=0b01100100;  //+   //Entry mode set L    01(i/d)s0000 modificar a gusto
    enable();
    __delay_ms(20);
    //INICIALIZACION INICIALIZACION INICIALIZACION INICIALIZACION
    //__delay_ms(1);
     
}

void ini_lcd(void){
                                
    __delay_ms(20);             //inicializacion para hitachi 44780
    
    PORTLCD=0b100;  //+
    TRISPORTLCD=0;
    
    PORTLCD=0x34; //+
    enable();               //3
        __delay_ms(5);
    PORTLCD=0x34;//+
    enable();               //3
        __delay_us(150);
    PORTLCD=0x34;//+
    enable();               //3
        __delay_us(150);
    PORTLCD=0x24;//+
    enable();               //2
        __delay_us(150);
    enviar(0x28);                   //0010nf00
        __delay_us(150);
    enviar(8);
        __delay_us(150);
    enviar(1);              //1
        __delay_ms(4);
    enviar(6);              // 000001(i/d)s
        __delay_us(40);     //F
}

void enable(void){
    /*__delay_us(2); //era 2, cambie a 20 por debug
    e_e=1;
    __delay_us(2); //era 2, cambie a 20 por debug
    e_e=0;
    __delay_us(2); //era 2, cambie a 20 por debug
     */
    __delay_us(2); //era 2, cambie a 20 por debug
    e_e=0;
    __delay_us(2); //era 2, cambie a 20 por debug
    e_e=1;
    __delay_us(2); //era 2, cambie a 20 por debug
}

void display_cursor_blink(unsigned char d, unsigned char c, unsigned char b){ //listo
    unsigned char intruccion;
    instruccion=0b1000+(d<<2)+(c<<1)+b;
    enviar(instruccion);
    __delay_us(40);
}   //listo

void clear_display(){
    unsigned char instruccion;
    instruccion=1;
    enviar(instruccion);
    __delay_ms(2);
}   //listo

void incdec_shift(unsigned char i_d, unsigned char s){
    unsigned char instruccion;
    instruccion=0b100+(i_d<<1)+s;
    enviar(instruccion);
    __delay_us(40);
}   //listo

void function_set(){
    unsigned char instruccion;
    instruccion=0b100000+(bus_display<<4)+(lineas_display<<3)+(fuente_display<<2);
    enviar(instruccion);
    __delay_us(40);
}   //listo

void set_cgram_adress(unsigned char adress){
    unsigned char instruccion;
    instruccion=0b1000000+adress;
    enviar(instruccion);
    __delay_us(40);
}   //listo

void set_ddram_adress(unsigned char adress){
    unsigned int instruccion;
    instruccion=0b10000000+adress;
    enviar(instruccion);
    __delay_us(40);
}   //listo

void dd_cg_write(unsigned char data){
    unsigned int instruccion;
    instruccion=0b1000000000+data;
    enviar(instruccion);
    __delay_us(40);
}   //listo

void enviar(unsigned int instr){   //formato de instruccion igual al de la hoja de datos:
                          //instr= RS-RW-DB7-DB6-DB5-DB4-DB3-DB2-DB1-DB0
    //manda en 4 bits, de a dos partes
    unsigned char L,H;
    H=instr&0xF0;
    L=(instr&0xF)<<4;
    // SI SE ANULA RW, BORRAR LOS DESPLAZAMIENTOS QUE GASTAN MEMORIA Y TIEMPO DE GUSTO
    PORTB=H+((instr&0b0100000000)>>7)+((instr & 0b1000000000) >> 9)+4;
    enable();
    // SI SE ANULA RW, BORRAR LOS DESPLAZAMIENTOS QUE GASTAN MEMORIA Y TIEMPO DE GUSTO
    PORTB=L+((instr&0b0100000000)>>7)+((instr & 0b1000000000) >> 9)+4;
    enable();
}

void print(char s[]){
    
    unsigned char i=0;
    
    while(s[i]!='\0'){
        dd_cg_write(s[i]);
        i++;
    }
}

void print_var(unsigned char var){
    unsigned char decenas;
    if(var>199){
        dd_cg_write('2');
        var-=200;
    }else if(var>99){
        dd_cg_write('1');
        var-=100;
    }else{
        dd_cg_write('0');
    }
    decenas=var/10;
    dd_cg_write(decenas+48);
    dd_cg_write(var-decenas*10+48);   
}