/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "timer.h"
#include "pwm.h"
#include "uart.h"

void pwmSetRange( int period )
{
    int pwm_value;
    int range;

    range = *PWM3_PERIOD;           //Get period
    pwm_value = range - *PWM3_DUTY; //Get duty
    *PWM3_CTRL &= ~(1<<0);          //Disable PWM
    *PWM3_PERIOD = period;          //Set period PWM
    *PWM3_CTRL |= (1<<0);           //Enable PWM
    pwmWrite( pwm_value );
}

void pwmSetClock( int value )
{
    int divisor;

    divisor = value & 0xff;
    *PWM3_CTRL &= ~(1<<0);        //Disable PWM
    *PWM3_CTRL = (*PWM3_CTRL & ~(0xff << 16)) | ((0xff & (divisor/2)) << 16) | (1<<9) ;                           //PWM div
    *PWM3_CTRL |= (1<<0);         //Enable PWM
}

void pwmMode( void )
{
    *GPIO7CH = (0x7000 << 16) | (0x3000);
    udelay( 5000 );
    pwmSetRange( 1024 );       // Default range of 1024
    pwmSetClock( 124 );        // 74.25Mhz / 124 = 599KHz
}

void pwmWrite( int value )
{
    int range;

    range = *PWM3_PERIOD;
    *PWM3_CTRL &= ~(1<<0);        //Disable PWM
    *PWM3_DUTY = range - value;   //Set duty
    *PWM3_CTRL &= ~(1<<5);
    *PWM3_CTRL |= (1<<1);
    *PWM3_CTRL &= ~(1<<2);
    *PWM3_CTRL |= (1<<4);
    *PWM3_CTRL |= (1<<0);         //Enable PWM
}

void pwmToneWrite( int freq )
{
    int divi;
    int pwm_clock;
    int range;
    int rangediv2;

    divi = ((*PWM3_CTRL >> 16) & 0xff) << 1;
    if(divi == 0)
        divi = 512;
    if (freq == 0)
        pwmWrite( 0 );
    else {
        pwm_clock = 599000; //74250000 / divi;
        //range = pwm_clock / freq;
        range = 0;
        while( pwm_clock > freq){
           pwm_clock -= freq;
           range += 1;
        }
        rangediv2 = range >> 1;
        pwmSetRange( range );
        pwmWrite ( rangediv2 );
    }
}

void pwm_led_test( void )
{
    int i;
    int bright;

    pwmMode();
    for (i=0; i< 10; i++) {
        for (bright = 0; bright < 1024; bright=bright+4)
        {
          pwmWrite( bright );
          udelay( 5000 );
        }

        for (bright = 1023; bright >= 0; bright=bright-4)
        {
          pwmWrite( bright );
          udelay( 5000 );
        }
    }
}

void tone( int melody, int duration, int duration2 ) 
{
    int melodydiv2;

    melodydiv2 = melody >> 1;
    if ( melody == 0 ) {
       udelay( duration );
    } else {
       pwmToneWrite( melody );
       pwmWrite( melodydiv2 );
       udelay( duration );
       pwmWrite( 0 );
    }
    udelay( duration2 ); // * 0.8 );
}

void tongsong( void )
{
    int thisNote;
    int duration;
    int duration2;
    int tmp;
  
    int melody[] = {
        262, 196, 196, 220, 196, 0, 247, 262
    };
  
    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
        4, 8, 8, 4, 4, 4, 4, 4
    };
 
    pwmMode(); 
    for ( thisNote = 0; thisNote < 8; thisNote++ ) {
       tmp = noteDurations[thisNote];
       //duration = 1000000 / tmp;
       if ( tmp == 4 ) {
           duration  = 250000;
           duration2 = 200000;
       } else if ( tmp == 8 ) {
           duration  = 125000;
           duration2 = 100000;
       }
       tone( melody[thisNote], duration, duration2 );
    }
}

void servo( void )
{
    int i;
  
    pwmMode();
    pwmSetClock( 445 );    // 74.25 MHz / 445 / 1024 = 163 Hz
    pwmSetRange( 1024 );
    pwmWrite( 205 );       // min 205 = 0 degree, max 845 = 180 degree
  
    for (i=0; i< 3; i++) {
      pwmWrite( 205 );
      printf( "0 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 525 );
      printf( "90 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 845 );
      printf( "180 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 525 );
      printf( "90 degree\r\n" );
      udelay( 1000000 );
    }
    pwmWrite( 0 );
}
