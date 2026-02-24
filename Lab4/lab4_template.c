/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
    lcd_init();
    lcd_printf("Start");
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	cyBot_uart_init();

	            // Don't forget to initialize the cyBot UART before trying to use it

	uint8_t button;
	int i;
	int length;
	
	while(1)
	{

      button = button_getButton();
      char buffer[30];
      if (button == 4){
          sprintf(buffer, "Button 4 is now pressed\r\n");
      }else if (button == 3){
          sprintf(buffer, "Button 3 is now pressed\r\n");
      }else if (button == 2){
          sprintf(buffer, "Button 2 is now pressed\r\n");
      }else if (button == 1){
          sprintf(buffer, "Button 1 is now pressed\r\n");
      }else {
          sprintf(buffer, "No button is pressed\r\n");
      }
      lcd_printf("Button: %d", button);

      length = sizeof(buffer) / sizeof(buffer[0]);

      for(i=0; i<length; i++){
          cyBot_sendByte(buffer[i]);
      }


      timer_waitMillis(200);



	}

}
