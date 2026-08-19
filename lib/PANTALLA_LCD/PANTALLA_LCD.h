#ifndef PANTALLA_LCD_H
#define PANTALLA_LCD_H
#include"stm32f103xb.h"

typedef struct{
   GPIO_TypeDef* puerto;
   int datos[8];
   int rs;
   int rw;
   int vo;
   int cursor;
   int col;
   int fil;

}LCD_t;

void lcd_init(LCD_t*);
void lcd_clear(LCD_t*);
void lcd_setCursor(LCD_t* );
void lcd_print();
void lcd_scrollDisplayLeft(LCD_t* );
void lcd_scrollDisplayRight(LCD_t* );
void lcd_backlight();
void lcd_noBacklight();
void lcd_createChar (int num, int datos);

#endif
