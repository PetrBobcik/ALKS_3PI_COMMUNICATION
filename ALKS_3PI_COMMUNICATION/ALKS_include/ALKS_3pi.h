/*
 *  Name:     ALKS_3pi.h
 *  Autor:    Petr Bobcik
 *  Created:  8.2.2019
 *  Modified: 8.2.2019
 *  Description: This file contains function from Pololu 3pi. This file allows to
 *               controll Pololu 3pi from ALKS.
 */
#include <stdio.h>
#include <Arduino.h>

// Avakar protocol -> 0x80 | command (4 bity) | data length (4 bity) | data

#ifndef ALKS_3PI
#define ALKS_3PI

#define BUTTON_A    1 << 1
#define BUTTON_B    1 << 4
#define BUTTON_C    1 << 5

#define SERIAL_BAUD_RATE  115200
#define AVAKAR_HEADER     0x80

#define MOTOR_COMMAND    0
#define DISPLAY_COMMAND  4
#define RS232_COMMAND    16
#define TICK_COMMAND     25
#define SENSOR_COMMAND   28
#define BATTERY_COMMAND  34
#define BUTTON_COMMAND   35
#define BUZZER_COMMAND   39


// Motor functions
void setLeftMotor(int16_t speed){
    uint8_t command_and_data_len = (MOTOR_COMMAND<<2) | (0x1);
    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    Serial.write(speed);
}
void setRightMotor(int16_t speed){
    uint8_t command_and_data_len = ((MOTOR_COMMAND+1)<<2) | (0x1);
    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    Serial.write(speed);
}

void setMotorPower(int16_t left, int16_t right){
    uint8_t command_and_data_len = ((MOTOR_COMMAND+2)<<2) | (0x2);
    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    
    if(left < 0){
        left *= -1;
        left |= 0x80;
    }

    if(right < 0){
        right *= -1;
        right |= 0x80;
    }

    Serial.write( left ); 
    Serial.write( right );
}

void setMotorPowerID(uint8_t motor, int16_t speed){
    //MOTOR_COMMAND+3
}


// display functions
class display{    
public:
    inline void print(const char *str);
    void printNumber(int16_t n, uint8_t width = 0);
    inline void send_data(uint8_t data);
    inline void clear();
    void showCursor(uint8_t cursorType);
    inline void hideCursor();
    void moveCursor(uint8_t direction, uint8_t num);
    void scroll(uint8_t direction, uint8_t num, uint16_t delay_time);
    void gotoXY(uint8_t x, uint8_t y);
    inline void printNumToXY(int16_t num, uint8_t x, uint8_t y);
    inline void send_cmd(uint8_t cmd);
    inline void send_4bit_cmd(uint8_t cmd);
};

// rs232 functions
class rs232{
public:
    char get(){
       /* uint8_t command_and_data_len = (RS232_COMMAND<<2) | (0x2);
        Serial.write(AVAKAR_HEADER);
        Serial.write(command_and_data_len);
        
        while(!Serial.available());
        return Serial.read();*/
    };

    bool peek(char & ch);
    void sendCharacter(char ch);  
    void send(const char * str);
    void sendHexByte(uint8_t byte);
    void sendNumberHex(int16_t n, uint8_t width = 0);
    void sendNumber(int16_t n, uint8_t width = 0);
    void dumpNumber(int16_t n);
    void wait();
};

// timer functions
inline void delayMicroseconds(uint16_t microseconds);
uint32_t getTicksCount();
void resetTicks();

// Surface and battery sensors functions
inline int16_t getSensorValue(uint8_t index){
    uint16_t result = 0;
    uint8_t command_and_data_len = (SENSOR_COMMAND<<2) | (0x1); 

    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    Serial.write(index);

    while( Serial.peek() == -1 );   
    result = Serial.read();         // read lower Byete from serial
    while( Serial.peek() == -1 );   
    result |= (Serial.read() << 8); // read upper Byete from serial and merge them together
    return result;                  // 0-1024
} 

int16_t getLinePos(bool white_line = false){
    uint8_t command_and_data_len = ((SENSOR_COMMAND+1)<<2) | (0x2);
    
    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    Serial.write(white_line);
}

inline void calibrate_sensors(){
    
}

void cal_round();
void store_sensor_cal(uint16_t address);
void load_sensor_cal(uint16_t address);
inline uint16_t getBatteryVoltage();

// button functions
inline bool isPressed(uint8_t buttons){
    uint8_t command_and_data_len = (BUTTON_COMMAND<<2) | (0x1);
    Serial.write(AVAKAR_HEADER);
    Serial.write(command_and_data_len);
    Serial.write(buttons);
    while( Serial.peek() == -1 );

    if( Serial.read() == '1' )
        return true;

    return false;
}

inline uint8_t waitForPress(uint8_t buttons){
    while( !isPressed(buttons) );
    return 1;
}

inline uint8_t waitForRelease(uint8_t buttons){
    while( isPressed(buttons) );
    return 0;
}

inline void waitForButton(uint8_t buttons){
    bool state = isPressed( buttons );
    if(state)
        while(isPressed(buttons));
    else
        while(!isPressed(buttons));
}

// EEPROM functions

// buzzer functions
class buzzer{
public:
    void start();
    void stop();
    void set(uint16_t time_on = 0, uint16_t time_off = 0, bool run = true);  
    bool isStarted();
};


#endif //ALKS_3PI