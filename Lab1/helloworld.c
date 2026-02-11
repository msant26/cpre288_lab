/// Prints text as a rotating banner
/**
 * This program prints "Microcontrollers are lots of fun!" to the LCD screen
 * in a rotating banner manner
 * @author Michael Santiago
 * @date 01/27/2026
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int charSelect, spaces, loops, pos, i;

int main (void) {
    char text[] = "Microcontroller are fun!";
    int textArrLen = sizeof(text) / sizeof(text[0]);

    char buffer[textArrLen + 40];
    strcat(buffer, "                    ");
    strcat(buffer, text);
    strcat(buffer, "                    ");
    int arrLen = sizeof(buffer) / sizeof(buffer[0]);

    char target[20];

    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init();   // Initialize the LCD screen.  This also clears the screen.
    while(1){
        spaces = 19;
        pos = 0;
        for(loops = 0; loops < arrLen - 20; loops++){
            i = 0;
            for(charSelect = pos; charSelect < spaces + pos; charSelect++){
                target[i] = buffer[charSelect];
                i++;
            }

            lcd_printf("%s", target);
            pos++;
            timer_waitMillis(300);
        }
    }
    return 0;
}
