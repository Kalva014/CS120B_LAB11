/*	Author: kennethalvarez
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//#include "bit.h"

#ifdef _INPUT_
#include "io.c"
#endif

//#include "io.h"
#include "keypad.h"
//#include "lcd_8bit_task.h"
//#include "queue.h"
//#include "scheduler.h"
//#include "seven_seg.h"
//#include "stack.h"
#include "timer.h"

unsigned char led0_output = 0x00;
unsigned char led1_output = 0x00;
unsigned char pause = 0;
unsigned char x;


unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}


typedef struct _task{
	// Tasks should have members that include: state, period,
	//a measurement of elapsed time, and a function pointer.
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;


enum keypad_States {GetKey};

int keypadSMTick(int state) {
	switch(state) { //transitions
		case GetKey:
			state = GetKey;
			break;
		default:
			state = GetKey;
			break;
	}
	
	switch(state) { //actions
		case GetKey:
			x = GetKeypadKey();
			switch(x) {
				case '\0': 
					//PORTB = 0x1F; 
					//LCD_Cursor(1);
					//LCD_ClearScreen();
					//LCD_WriteData(x);
					break;
				case '1': 
					//PORTB = 0x01; 
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '2':
					//PORTB = 0x02; 
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
                		case '3': 
					//PORTB = 0x03;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					 break;
				case '4':
					//PORTB = 0x04;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '5':
					//PORTB = 0x05;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '6':
					//PORTB = 0x06;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '7':
					//PORTB = 0x07;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '8': 
					//PORTB = 0x08;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '9': 
					//PORTB = 0x09;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case 'A': 
					//PORTB = 0x0A;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case 'B': 
					//PORTB = 0x0B;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case 'C': 
					//PORTB = 0x0C;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case 'D': 
					//PORTB = 0x0D;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '*': 
					//PORTB = 0x0E;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '0': 
					//PORTB = 0x00;	
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				case '#': 
					//PORTB = 0x0F;
					//LCD_Cursor(1);
                                        LCD_ClearScreen();
					LCD_WriteData(x);
					break;
				default: 
					//PORTB = 0x1B; 
					break;
			}
		default:
			break;	
	}
	return state;	
}


int main(void) {
	/* Insert DDR and PORT Initialization */
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;//this might be wrong 
	DDRD = 0xFF; PORTD = 0x00;
		

	static task task5;
	task *tasks[] = {&task5};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;

	task5.state = start; //THE KEYPAD SM ADDED FOR PART 1
	task5.period = 100;
	task5.elapsedTime = task5.period;
	task5.TickFct = &keypadSMTick;

	unsigned long GCD = tasks[0]->period;
	for(unsigned short i = 1; i < numTasks; i++) {
		GCD = findGCD(GCD, tasks[i]->period);
	}	
	
	TimerSet(GCD);
	TimerOn();

	LCD_init();
	unsigned short i;
	
	
	/* Insert your solution below */
	while(1) {
		for(i = 0; i < numTasks; i++) {
			if(tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
	
			tasks[i]->elapsedTime += GCD;
		}

		while(!TimerFlag);
		TimerFlag = 0;
	}
        return 0;
}
