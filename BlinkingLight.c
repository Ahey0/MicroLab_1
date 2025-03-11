#include <stdio.h>
#include <mega16.h>
#include <delay.h>

void blink_one_by_one() {
    int i;
    for ( i=0 ; i < 8; i++) {
        PORTB = (1 << i);
        delay_ms(50);
    }
    return;
}

void alternate_four_leds() {
    PORTB = 0x0F;  
    delay_ms(50);
    PORTB = 0xF0;  
    delay_ms(50);
    return;
}

void pairs_on_off() {
    PORTB = 0x33;  // 00110011
    delay_ms(50);
    PORTB = 0xCC;  // 11001100
    delay_ms(50);
    return;
}

void main() {
    DDRB = 0xFF;  // Set PORTB as output (LEDs)
    DDRD = 0x00;  // Set PORTD as input (Switches)

    while (1) {
        if (PIND & (1 << PIND0)) 
{ 
            int mode = (PIND >> 1) & 0x03; 
            
            switch (mode) {
                case 0b00:
                    PORTB = 0x00; 
                    break;
                case 0b01:
                    blink_one_by_one();
                    break;
                case 0b10:
                    alternate_four_leds();
                    break;
                case 0b11:
                    pairs_on_off();
                    break;
            }
        } else {
            PORTB = 0x00; 
        }
    }
}
