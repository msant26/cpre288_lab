#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include "uart.h"


void scanForThinnest();

int findEdges();

double findDistance();
