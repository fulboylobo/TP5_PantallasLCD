#define PANTALLA_LCD_h
#include "stm32f103xb.h"
void lcd_init(LCD_t*  lcd ){
    
        if(lcd->puerto=GPIOB){
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
    }else if(lcd->puerto=GPIOC){
        RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
    }
        for(int i=0;i<8;i++){
            if(lcd->datos[i]<8){
                lcd->puerto->CRL&=~(0xf<<(lcd->datos[i]*4));
                lcd->puerto->CRL|=(0x1<<(lcd->datos[i]*4));
            }else{
                lcd->puerto->CRH&=~(0xf<<((lcd->datos[i]*4)%8));
                lcd->puerto->CRH|=(0x1<<((lcd->datos[i]*4)%8));
            }
        }
        if(lcd->rs<8){
            lcd->puerto->CRL&=~(0xf<<(lcd->rs*4));
            lcd->puerto->CRL|=(0x1<<(lcd->rs*4));
        }else{
            lcd->puerto->CRH&=~(0xf<<((lcd->rs*4)%8));
            lcd->puerto->CRH|=(0x1<<((lcd->rs*4)%8));
        }

        if(lcd->rw<8){
            lcd->puerto->CRL&=~(0xf<<(lcd->rw*4));
            lcd->puerto->CRL|=(0x1<<(lcd->rw*4));
        }else{
            lcd->puerto->CRH&=~(0xf<<((lcd->rw*4)%8));
            lcd->puerto->CRH|=(0x1<<((lcd->rw*4)%8));
        }

        if(lcd->vo<8){
            lcd->puerto->CRL&=~(0xf<<(lcd->vo*4));
            lcd->puerto->CRL|=(0x1<<(lcd->vo*4));
        }else{
            lcd->puerto->CRH&=~(0xf<<((lcd->vo*4)%8));
            lcd->puerto->CRH|=(0x1<<((lcd->vo*4)%8));
        }
}
void lcd_backlight(LCD_t* lcd){
    lcd->puerto->BSRR|=(1<<(lcd->rs+16));
    lcd->puerto->BSRR|=(1<<(lcd->rw+16));
    for(int i=4;i<8;i++){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
    lcd->puerto->BSRR|=(1<<(lcd->datos[3]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[2]));
}
void lcd_noBacklight(LCD_t* lcd){
    lcd->puerto->BSRR|=(1<<(lcd->rs+16));
    lcd->puerto->BSRR|=(1<<(lcd->rw+16));
    for(int i=4;i<8;i++){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
    lcd->puerto->BSRR|=(1<<(lcd->datos[3]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[2]+16));

}

void lcd_scrollDisplayLeft(LCD_t* lcd){
    lcd->puerto->BSRR|=(1<<(lcd->rs+16));
    lcd->puerto->BSRR|=(1<<(lcd->rw+16));
    for(int i=5;i<8;i++){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
    lcd->puerto->BSRR|=(1<<(lcd->datos[4]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[3]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[2]+16));
}
void lcd_scrollDisplayRight(LCD_t* lcd){
    lcd->puerto->BSRR|=(1<<(lcd->rs+16));
    lcd->puerto->BSRR|=(1<<(lcd->rw+16));
    for(int i=5;i<8;i++){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
    lcd->puerto->BSRR|=(1<<(lcd->datos[4]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[3]));
    lcd->puerto->BSRR|=(1<<(lcd->datos[2]));
}
void lcd_clear(LCD_t* lcd){
    lcd->puerto->BSRR|=(1<<(lcd->rs+16));
    lcd->puerto->BSRR|=(1<<(lcd->rw+16));
    for(int i=1;i<8;i++){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
    lcd->puerto->BSRR|=(1<<(lcd->datos[0]));
    
}
void lcd_setCursor(LCD_t* lcd, int col, int fil){
    uint8_t row_shift[2]={0x00,0x40};
    uint8_t comando=col+row_shift[fil];
    lcd_send(lcd, comando, 0);

}
void lcd_send (LCD_t *lcd, uint8_t dato, int charcmd){
    if(charcmd){
        lcd->puerto->BSRR|=(1<<(lcd->rw));
    }else{
        lcd->puerto->BSRR|=(1<<(lcd->rw+16));

    }
lcd->puerto->BSRR|=(1<<(lcd->rs));
for(int i=7;i>=0;i--){
   
    if(dato&(1<<lcd->datos[i])){
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]));
    }else{
        lcd->puerto->BSRR|=(1<<(lcd->datos[i]+16));
    }
}

}

void lcd_print(LCD_t* lcd, char *txt){
    while(*txt){
        lcd_send(lcd, *txt, 0 );
        txt++;
    }
}
