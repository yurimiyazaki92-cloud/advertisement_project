#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include "stdlib.h" // for the random number.
#include <time.h> // to check the time.

// Now I do not mention "scroll text","clock"

// https://wokwi.com/projects/416241646559459329

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)


void BlinkText(HD44780 &lcd, const char* text){
    for(int i = 0; i <= 40; i++) {

        lcd.Clear();
        lcd.GoTo(0,0);
        lcd.WriteText((char*)text);
        _delay_ms(250);

        lcd.Clear(); 
        _delay_ms(250);
    }
}


void ScrollSwedish(HD44780 &lcd, const char* text) 
{
    int len = 0;
    while(text[len] != '\0') len++;  


    char buffer[30];
    snprintf(buffer, sizeof(buffer), "%s                ", text);

    int totalLen = len + 5; 
    int i = 0;

    uint16_t elapsed = 0; 

    while(elapsed < 20)
    {
        lcd.Clear();
        lcd.GoTo(0,0);
        lcd.WriteSwedish(&buffer[i]);
        _delay_ms(1000);

        i++;
        if(i >= totalLen) i = 0; // 最初に戻る

        elapsed += 1000 / 1000; // 秒換算
    }
    lcd.Clear(); 
}

int main(void){
    init_serial();
    HD44780 lcd;
    int randomNumber;
    int adgroup;

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD
    lcd.GoTo(0,0);
    srand(ADC);

    while(1){
        
        randomNumber = rand() % 14500; // We assume that the advertisers have 14500 tickets in total.

        // get random ad-group.
        if(randomNumber >=0 && randomNumber < 5000 && adgroup != 1){
            adgroup = 1;
        }
        else if(randomNumber >=5000 && randomNumber < 8000 && adgroup != 2){
            adgroup = 2;
        }
        else if(randomNumber >=8000 && randomNumber < 9500 && adgroup != 3){
            adgroup = 3;
        }
        else if(randomNumber >=9500 && randomNumber < 13500 && adgroup != 4){
            adgroup = 4;
        }
        else if(randomNumber >=13500 && randomNumber < 14500&& adgroup != 5){
            adgroup = 5;
        }
        else{continue;}

        // get advertisemnts for each group.

        if (adgroup == 1) {
            int randomHH = rand() % 3;

            switch(randomHH){
                case 0:
                ScrollSwedish(lcd, "Köp bil hos Harry");
                break;
                case 1:
                lcd.WriteSwedish("En god bilaffär (för Harry!)");
                _delay_ms(20000);
                break;
                case 2:
                BlinkText(lcd, "Hederlige Harrys Bilar");
                break;
            }
            
        }
        else if(adgroup == 2){
            int randomFA = rand() % 2;
            switch(randomFA){
                case 0:
                ScrollSwedish(lcd, "Köp paj hos Farmor Anka");
                break;
                case 1:
                lcd.WriteSwedish("Skynda innan Mårten ätit alla pajer");
                _delay_ms(20000);
                break;
            };
            

        }
        else if(adgroup == 3){
            time_t now = time(NULL);
            struct tm *t = localtime(&now); //check the time and change the format to "minites".
            if(t->tm_min%2 == 0){
                ScrollSwedish(lcd, "Låt Petter bygga åt dig");
            }
            else{
                lcd.WriteText("Bygga svart? Ring Petter");
                _delay_ms(20000);
            };
            

        }
        else if(adgroup == 4){
            int randomLB = rand() % 2;
            switch(randomLB){
                case 0:
                lcd.WriteSwedish("Mysterier? Ring Långben");
                _delay_ms(20000);
                break;
                case 1:
                lcd.WriteSwedish("Långben fixar biffen");
                _delay_ms(20000);
                break;
            };
            
        }
        else if(adgroup == 5){
            lcd.WriteSwedish("Synas här? IOT:s Reklambyrå");
            _delay_ms(20000);

        };
        lcd.Clear();

    };
    return 0;


    
}
