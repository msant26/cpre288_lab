/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping.h"
#include "Timer.h"

// Global shared variables
// Use extern declarations in the header file

volatile uint32_t g_start_time = 0;
volatile uint32_t g_end_time = 0;
volatile enum{LOW, HIGH, DONE} g_state = LOW; // State of ping echo pulse
volatile uint32_t rising_time = 0;
volatile uint32_t falling_time = 0;
volatile uint32_t pulse_width = 0;
volatile uint8_t done = 0;
volatile uint8_t overflow = 0;

void ping_init (void){

  // YOUR CODE HERE

    // Enable clock
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x08;

    // Clock wait loop
    while((SYSCTL_PRGPIO_R & 0x02) == 0){};
    while((SYSCTL_PRTIMER_R & 0x08) == 0){};

    // Enable alternate functions
    GPIO_PORTB_AFSEL_R |= 0x08;

    // Enable digital functions
    GPIO_PORTB_DEN_R |= 0x08;

    // Select alternate function
    GPIO_PORTB_PCTL_R = 0x7000;

    // Configure 16 Bit mode
    TIMER3_CFG_R = 0x04;

    // Configure input edge-time
    TIMER3_TBMR_R = 0x07;

    // 8bit prescaler for 24bit timer
    TIMER3_TBPR_R = 0xFF;
    TIMER3_TBILR_R = 0xFFFF;

    // Capture both rising and falling
    TIMER3_CTL_R |= 0xC00;

    // Enable interrupts
    TIMER3_IMR_R |= 0x400;

    // Turn on timer
    TIMER3_CTL_R |= 0x100;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();
}

void ping_trigger (void){
    g_state = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x08;

    // Low state (2us to allow low to set)
    GPIO_PORTB_DATA_R &= ~0x08;
    timer_waitMicros(2);

    // High state (5us)
    GPIO_PORTB_DATA_R |= 0x08;
    g_state = HIGH;
    timer_waitMicros(5);

    // Return to low state
    GPIO_PORTB_DATA_R &= ~0x08;
    g_state = LOW;

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0xF00;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x08;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

void TIMER3B_Handler(void){

    // Check if this interrupt is from capture event
    if (TIMER3_MIS_R & 0x400) {

        // Clear the interrupt
        TIMER3_ICR_R = 0x400;

        // Read 24-bit timestamp
        uint32_t timestamp = TIMER3_TBR_R & 0x00FFFFFF;

        // Edge handling
        if (g_state == LOW) {
            rising_time = timestamp;

            g_state = HIGH;

            // capture falling edge
            TIMER3_CTL_R &= ~0x0C00;
            TIMER3_CTL_R |= 0x0400;
        }
        else {
            // Falling edge
            falling_time = timestamp;

            // Compute pulse width
            if (falling_time >= rising_time){
                pulse_width = falling_time - rising_time;
                overflow = 0;
            }
            else{
                pulse_width = (0x00FFFFFF - rising_time) + falling_time;
                overflow = 1;
            }

            done = 1;

            // Prepare for next measurement → back to rising edge
            TIMER3_CTL_R &= ~0x0C00;
            TIMER3_CTL_R |= 0x0000;   // Rising edge

            g_state = LOW;
        }
    }
}

float ping_getDistance (void){

    // YOUR CODE HERE

}
