/*
 * 3pi_alks.cpp
 *
 * Created: 24/04/2019
 * Author: Petr Bobcik
 * Description: Pololu 3pi is controlled by ALKS. This .cpp reads incomming Bytes from ALKS and
 *				do corresponding activity.
 */ 

#define JUNIOR_RS232_BPS 38400
#include "3piLibPack.h"
#define AVAKAR_HEADER	0x80
#define COMMAND_OFFSET	0x00f0
#define DATA_LEN_OFFSET 0x000f

#define MOTOR_COMMAND    0
#define DISPLAY_COMMAND  4
#define RS232_COMMAND    16
#define TICK_COMMAND     25
#define SENSOR_COMMAND   28
#define BATTERY_COMMAND  34
#define BUTTON_COMMAND   35
#define BUZZER_COMMAND   39


// Avakar protocol ->x80 | command (4 bity) | data length (4 bity) | data

void run(){ 	
	int8_t motor_l = 0;
	int8_t motor_r = 0;
	int16_t speed   = 0;

	while(true){
		while( rs232.get() != 0x80);
		
		switch(rs232.get() >> 2){		// read command number
			case MOTOR_COMMAND:
				speed = (int16_t)  rs232.get();
				setLeftMotor( speed );
				break;
				
			case MOTOR_COMMAND+1:
				speed = (int16_t)  rs232.get();
				setRightMotor( speed );
				break;
			
			case MOTOR_COMMAND+2:
				motor_l		=  rs232.get();
				motor_r		=  rs232.get();
				
				if( motor_l & 0x80 ){
					motor_l &= 0x7f;
					if(motor_l > 100)
						motor_l = 100;
					motor_l *= -1;
				}
				if( motor_r & 0x80 ){
					motor_r &= 0x7f;
					if(motor_r > 100)
						motor_r = 100;
					motor_r *= -1;
				}
				
				setMotorPower( motor_l, motor_r );
				break;
				
			case MOTOR_COMMAND+3:
				break;
			
			case BUTTON_COMMAND:
				uint8_t button = rs232.get();
				if( isPressed( button ) ){
					rs232.sendCharacter( '1' );
				}
				else{
					rs232.sendCharacter( '0' );
				} 
				break;
		}
	}
}