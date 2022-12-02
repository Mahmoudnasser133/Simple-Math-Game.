/*
 * simple_math_game.c
 *
 * Created: 21-Nov-22 1:08:25 PM
 *  Author: nasser
 */ 


#include <avr/io.h>
#include "LCD.h"

#define F_CPU 8000000UL
#include <util/delay.h>
#include "keypad_driver.h"
#include <avr/interrupt.h>
#include "timer.h"

volatile  int count_time =0;
int main(void)
{
   LCD_vInit();
   LCD_vSend_string("hello kids");
   _delay_ms(500);
   LCD_clearscreen();
   timer_CTC_init_interrupt();
   char i =0;
   char arr[]={'8','6','5','7','9'};
	char arr2[]={8,6,5,7,9};  
   char num[]={'1','3','2','4','5'};
	char num2[]={1,3,2,4,5};  
    char score =0;
   while (i<4)
   {
	   int x = 0xff;
	   unsigned char flag =0;
	LCD_clearscreen();
   LCD_vSend_char(num[i]);
   LCD_movecursor(1,3);
   LCD_vSend_char('+');
   LCD_movecursor(1,5);
   LCD_vSend_char('?');
   LCD_movecursor(1,7);
   LCD_vSend_char('=');
   LCD_movecursor(1,9);
	LCD_vSend_char(arr[4-i]); 
   keypad_vInit();

     int result=0;	
	do 
	{
		if (count_time>=500)
		{
			flag=1;
		}
	x=keypad_u8check_press();
	result = arr2[4-i] - num2[i];	
	} while (x==0xff && flag==0);
	
	
	 if(x== 0xff)
		{
			LCD_clearscreen();
			LCD_movecursor(2,3);
			LCD_vSend_string("Time Over");
			count_time=0;
		}
		
	else if (x==result+48)
	{
	LCD_clearscreen();
	LCD_movecursor(2,3);
	LCD_vSend_string("Well Done");
	score++;
	}

	else 
	{
	LCD_clearscreen();
	LCD_movecursor(2,3);
	LCD_vSend_string("Wrong Answer");
	}
	i++;
	_delay_ms(500);   
}
LCD_clearscreen();
LCD_vSend_string("score = ");
LCD_movecursor(1,9);
LCD_vSend_char(score+48);
}


ISR(TIMER0_COMP_vect)
{
	count_time++;
}