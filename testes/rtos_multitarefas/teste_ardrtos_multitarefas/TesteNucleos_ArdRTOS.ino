

#include <Arduino.h>
#include "ArdRTOS.h"

// blinks 
void loopBlink1();
void loopBlink2();
void loopBlink3();

void setup() {
    
    OS.addTask(loopBlink1);
    OS.addTask(loopBlink2);
    OS.addTask(loopBlink3);

    OS.begin();
    // execution never returns from begin
}

void loop() {
    // since OS.begin never returns, this function will never be called.
    // it is also entirely unecessary and can be removed in its entirety. 
}
/**
 * @brief 
 * 
 */
void loopBlink1() {

    Serial.println("Passou por loop 1");
    delay(10000);
    Serial.println("Passou por loop 1 após 10 segundos");
}


void loopBlink2() {
    Serial.println("Passou por loop 2");
    delay(10000);
    Serial.println("Passou por loop 2 após 10 segundos");
    
}

void loopBlink3() {
    Serial.println("Passou por loop 3");
    delay(20000);
    Serial.println("Passou por loop 3 após 20 segundos");
}
