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
volatile uint32_t interrupt_cnt = 0;

void ping_init (void){

    // enable clock
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x08;

    // clock wait loop
    while((SYSCTL_PRGPIO_R & 0x02) == 0){};
    while((SYSCTL_PRTIMER_R & 0x08) == 0){};

    // ensures timer is disabled
    TIMER3_CTL_R &= ~0x100;

    // enable alternate functions
    GPIO_PORTB_AFSEL_R |= 0x08;

    // enable digital functions
    GPIO_PORTB_DEN_R |= 0x08;

    // select alternate function
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xF000) | 0x7000;

    // configure 16 Bit mode
    TIMER3_CFG_R = 0x04;

    // configure input edge-time
    TIMER3_TBMR_R = 0x07;

    // 8bit prescaler for 24bit timer
    TIMER3_TBPR_R = 0xFF;
    TIMER3_TBILR_R = 0xFFFF;

    // capture both rising and falling
    TIMER3_CTL_R |= 0xC00;

    // clear flag and enable interrupts
    TIMER3_ICR_R = 0x400;
    TIMER3_IMR_R |= 0x400;

    // turn on timer
    TIMER3_CTL_R |= 0x100;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    // Interrupt register
    NVIC_EN1_R |= 0x10;

    IntMasterEnable();
}

void ping_trigger (void){
    done = 0;
    g_state = LOW;

    // disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;

    // disable alternate function
    GPIO_PORTB_AFSEL_R &= ~0x08;

    // low state (2us to allow low to set)
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_DATA_R &= ~0x08;
    timer_waitMicros(2);

    // high state (5us)
    GPIO_PORTB_DATA_R |= 0x08;
    g_state = HIGH;
    timer_waitMicros(5);

    // return to low state
    GPIO_PORTB_DATA_R &= ~0x08;
    g_state = LOW;

    // clear any interrupts
    TIMER3_ICR_R = 0x400;
    GPIO_PORTB_DIR_R &= ~0x08;

    // re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x08;
    timer_waitMicros(1);
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

void TIMER3B_Handler(void)
{
    if (TIMER3_MIS_R & 0x400)
    {
        // clear interrupt
        TIMER3_ICR_R = 0x400;

        // stores timestamp
        uint32_t timestamp = TIMER3_TBR_R & 0x00FFFFFF;

        if (g_state == LOW)
        {
            // rising edge
            rising_time = timestamp;
            g_state = HIGH;
        }
        else
        {
            // falling edge
            falling_time = timestamp;

            // subtracts rise from fall for width
            if (rising_time >= falling_time)
            {
                pulse_width = rising_time - falling_time;
                overflow = 0;
            }
            else
            {
                // overflow for negative val
                pulse_width = rising_time + (0x01000000 - falling_time);
                overflow = 1;
            }

            done = 1;
            g_state = LOW;
        }
    }
}

float ping_getDistance (void){

    // YOUR CODE HERE

}

