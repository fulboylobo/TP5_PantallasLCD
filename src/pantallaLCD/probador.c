#include"PANTALLA_LCD.H"
#include"stm32f103xb.h"
#include "delay.h"
#define left 2
#define right 3
#define cursor 4
#define apagar 5
#define clear 6

int main(void){

    delay_init();
    LCD_t lcd;
    lcd.puerto=GPIOA;
    for(int i=0;i<8;i++){
        lcd.datos[i]=7+i;
    }
   
   lcd.rs=0;
   lcd.rw=1;
   lcd.vo=15;
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

   for (int i=0;i<7;i++){
    GPIOA->CRL&=~(0xf<<(i*4));
    GPIOA->CRL|=(0x8<<(i*4));
    GPIOA->BSRR|=(1<<(i+16));
   }

   
    lcd_init(&lcd);
    lcd_backlight();
    while(1){
        if(GPIOA-> IDR&(1<<left)){
        lcd_scrollDisplayLeft(&lcd);
        }
        if(GPIOA-> IDR&(1<<right)){
        lcd_scrollDisplayRight(&lcd);}
        if(GPIOA-> IDR&(1<<cursor)){
        lcd_setCursor(&lcd, 0, 1 );}
        if(GPIOA-> IDR&(1<<apagar)){
        while(GPIOA-> IDR&(1<<apagar)){
        lcd_noBacklight();
        }
        lcd_backlight();
        }
        if(GPIOA-> IDR&(1<<clear)){
        lcd_clear(&lcd);
        }
        lcd_print(&lcd , 'me estoy enojando');
        delay_ms(500);

    }
}
